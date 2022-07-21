// Ceren Arkac ,28269, CS 300, HW3
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "strutils.h"
#include "SepChaining.h"
#include <chrono>
#include "Stack.h"
#pragma comment(linker, "/STACK:2000000")
#include "BST.h"
using namespace std;

// same purposes for structs as HW2
struct DocumentItem {
	string documentName;
	int count;

	DocumentItem()
	{
		documentName = "noDocName";
		count = 0;
	}

	DocumentItem(string documentName_, int count_):documentName(documentName_), count(count_){}

};


struct WordItem {

	string word;
	List<DocumentItem> * docs;

	WordItem()  // for notFound object
	{
		word = "noWord";
		docs = NULL;
	}
	
	WordItem(const string & word_)
	{
		word = word_; 
		DocumentItem notFound;
		docs = new List <DocumentItem>;
	}


};

int hash1(const WordItem & theElement, int tableSize)
{  
	return(hash2(theElement.word, tableSize));
}

bool operator!=(const WordItem & lhs, const WordItem & rhs) {return (!(lhs.word == rhs.word));}
bool operator<(const WordItem & lhs, const WordItem & rhs) {return (rhs.word > lhs.word);}
bool operator>(const WordItem & lhs, const WordItem & rhs) {return (rhs.word < lhs.word);}
bool operator==(const WordItem & lhs, const WordItem & rhs) {return (lhs.word == rhs.word);}

bool operator!=(const DocumentItem & lhs, const DocumentItem & rhs) {return (!(lhs.documentName == rhs.documentName));}
bool operator==(const DocumentItem & lhs, const DocumentItem & rhs) {return (lhs.documentName == rhs.documentName);}

ostream & operator << (ostream & os, const WordItem & element)   
{
	ostringstream ostr;
	ostr << element.word;
	os << ostr.str();
	return os;
}
// func declaretions
void QueryDocuments(BST <WordItem> * bst, vector <string> & readyQueries, vector <string> & files, int k);
void QueryDocuments(HashTable <WordItem> * ht, vector <string> & readyQueries, vector <string> & files, int k);

int main(){
	int numOfFiles;
	cout << "Enter number of input files: ";
	cin >> numOfFiles;
	vector <string> files;
	for (int i = 1; i <= numOfFiles; i++)
	{
		string fileNameX;
		cout << "Enter " << i << ". file name: ";
		cin >> fileNameX;
		files.push_back(fileNameX); // store the filenames
	}
	
	char ch;
	string word = "";
	vector <Stack<WordItem>> allWords; // store all the words in all the files
	bool fileSuccess = false;
	ifstream in;
	for (int i = 0; i < files.size(); i++)
	{
		fileSuccess = false;
		Stack <WordItem> wordsOfFileX;
		in.open(files[i].c_str());	
		if (!in.fail())
		{
			fileSuccess = true;
			bool checker = true;
			while (in.get(ch) || (in.eof() && checker == true))
			{
					if(in.eof())
						ch='.';
					if ((ch >= 97 && ch <= 122) || (ch >= 65 && ch <= 90 )) // if ch is alphabetical
					{
						word += ch;
					}
					else  // found a separator
					{
						if(in.eof())
							checker = false;
						if (word != ""){  
							ToLower(word);
							WordItem wordItemObj(word);
							wordsOfFileX.push(wordItemObj);
							if(in.eof()){
								checker = false;
							}
						}
						word = "";
					}
			}
		in.close();
		}
		allWords.push_back(wordsOfFileX);
	}
	if (fileSuccess)
	{
		WordItem notFound;
		BST <WordItem> * WordItemTree = new BST <WordItem> (notFound);
		HashTable <WordItem> * WordItemTable = new HashTable <WordItem> (notFound);

		for (int i = 0; i < allWords.size(); i++) // its size is = numOfFiles
		{
			while (!allWords[i].isEmpty()) // get the words of ith txt 
			{
				WordItem temp = allWords[i].topAndPop(); // get word from storage
				const WordItem & FoundHT = WordItemTable->find(temp); // check the word if it is available in our data structure
				const WordItem & FoundBST = WordItemTree->find(temp); // take const & in order not to call find again and again for the next steps
				if (FoundHT.word != "noWord" && FoundBST.word != "noWord") // existing word in data structures 
				{
					DocumentItem search; search.documentName = files[i];
					DocumentItem retrievedFoundHT = FoundHT.docs->find(search).retrieve(); // find the node of docs list with the current txt name
					DocumentItem retrievedFoundBST = FoundBST.docs->find(search).retrieve();
					if (retrievedFoundHT.documentName != search.documentName && retrievedFoundBST.documentName != search.documentName) // this is the first time we encounter this word IN THE CURRENT TXT
					{
						search.count = 1;
						// create a new node to its docs
						FoundHT.docs->insert(search, FoundHT.docs->zeroth());
						FoundBST.docs->insert(search, FoundBST.docs->zeroth());
					}
					else // this word is an existing word IN THE CURRENT TXT
					{
						// update the node with the CURRENT TXT DOCUMENTNAME
						FoundHT.docs->remove(search);
						FoundBST.docs->remove(search);
						retrievedFoundHT.count +=1;
						retrievedFoundBST.count +=1;
						FoundHT.docs->insert(retrievedFoundHT, FoundHT.docs->zeroth());
						FoundBST.docs->insert(retrievedFoundBST, FoundBST.docs->zeroth());
					}
				}
				else // new Hashtable element
				{
					// insert this wordItem
					WordItemTable->insert(temp); 
					WordItemTree->insert(temp); 
					// create a new node to its docs.
					DocumentItem search; search.documentName = files[i]; search.count = 1;
					WordItemTable->find(temp).docs->insert(search, WordItemTable->find(temp).docs->zeroth());
					WordItemTree->find(temp).docs->insert(search, WordItemTree->find(temp).docs->zeroth());
				}


			}
		}
		cout << endl;
		cout << "After preprocessing, the unique word count is " << WordItemTable->getNumOfEntries() <<  ". Current load ratio is " << WordItemTable->getLoadFactor() << endl;
		cout << "Enter queried words in one line: ";
		string query;
		char queryCh;
		cin.get();
		getline(cin, query);
		istringstream ss(query);
		string part;
		string readyQuery = "";
		vector <string> readyQueries;
		bool isWord = true;
		while (ss >> part)
		{
			isWord = true;

			for (int i = 0; i < part.size(); i++)
			{
				if (!(part[i] >= 97 && part[i] <= 122) || (part[i] >= 65 && part[i] <= 90 ))
				{
					isWord = false;
				}
			}

			if (isWord)
			{
				readyQueries.push_back(part);
			}
			else // we obtained the words in the previous lines. now its time to deal with the parts involving nonalphabetical characters
			{
				string newWord = "";
				for (int i = 0; i < part.size(); i++)
				{
		
					if ((part[i] >= 97 && part[i] <= 122) || (part[i] >= 65 && part[i] <= 90 ))
					{
						readyQuery += part[i];
					}
					else
					{
						if (readyQuery != "")
						{
							readyQueries.push_back(readyQuery);
							readyQuery = "";
						}
					}
				}
				if (readyQuery != "")
				{
					readyQueries.push_back(readyQuery);
				}
			}
		}
	
		int k = 100;
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < k; i++)
		{
			QueryDocuments(WordItemTree, readyQueries, files, i);
		}
		auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
		(std::chrono::high_resolution_clock::now() - start);

		start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < k; i++)
		{
			QueryDocuments(WordItemTable, readyQueries, files, i);
		}
		auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
		(std::chrono::high_resolution_clock::now() - start);
	
		cout << "\nTime: " << BSTTime.count() / k << "\n";
	
		cout << "\nTime: " << HTTime.count() / k << "\n";
	
		cout << "Speed Up: " <<  (double)BSTTime.count() / HTTime.count() << endl;
	}

	return 0;
}

void QueryDocuments(BST <WordItem> * bst, vector <string> & readyQueries, vector <string> & files, int k){
	string gotQuery;
	bool allQueryExists = true;
	vector <WordItem> foundWords;
	for (int i = 0; i < readyQueries.size(); i++)
	{
		gotQuery = readyQueries[i]; // get the parsed query one by one
		ToLower(gotQuery);
		WordItem queryWordItem(gotQuery);

		const WordItem & BSTFoundX = bst->find(queryWordItem); // search all the words of the query
		if (BSTFoundX.word == "noWord") 
		{
			allQueryExists = false; // // if this never changes, then it is means all query is found
		}
		else
		{
			foundWords.push_back(BSTFoundX);
		}

	}
	if (k == 99)
	{
		if (!allQueryExists)
		{
			cout << "No document contains the given query" << endl;
		}
		else // at least in some of the files or in all of them, query exits
		{
			DocumentItem search;
			for (int i = 0; i < files.size(); i++)
			{
				cout << "in Document " << files[i];
				search.documentName = files[i];
				for (int j = 0; j < foundWords.size(); j++)
				{
					cout << ", " << foundWords[j].word << " found " << foundWords[j].docs->find(search).retrieve().count << " times";
				}
				cout << "." << endl;
			}
		}
	}
	
}

void QueryDocuments(HashTable <WordItem> * ht, vector <string> & readyQueries, vector <string> & files, int k){
	string gotQuery;
	bool allQueryExists = true;
	int count = 0;
	vector <WordItem> foundWords;
	for (int i = 0; i < readyQueries.size(); i++)
	{
		gotQuery = readyQueries[i];
		ToLower(gotQuery);
		WordItem queryWordItem(gotQuery);

		const WordItem & HTFoundX = ht->find(queryWordItem);
		if (HTFoundX.word == "noWord")
		{
			allQueryExists = false;
		}
		else
		{
			foundWords.push_back(HTFoundX);
		}

	}
	if (k == 99)
	{
		if (!allQueryExists)
		{
			cout << "No document contains the given query" << endl;
		}
		else
		{
			DocumentItem search;
			for (int i = 0; i < files.size(); i++)
			{
				cout << "in Document " << files[i];
				search.documentName = files[i];
				for (int j = 0; j < foundWords.size(); j++)
				{
					cout << ", " << foundWords[j].word << " found " << foundWords[j].docs->find(search).retrieve().count << " times";
				}
				cout << "." << endl;
				
			}
		}
	}
	
}

