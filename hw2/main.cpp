// Ceren Arkac ,28269, CS 300, HW2
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "binarySearchTree.h"
#include "AVLtree.h"
#include <chrono>
#pragma comment(linker, "/STACK:2000000")

using namespace std;


struct ItemKey
{
	string title;
	string data;
	
	/*default constructor 
	--> While creating the BST, use this to create a dummy object and pass it for the notFound object. */
	ItemKey()
	{
		title = "noT";
		data = "noD";
	}

	ItemKey(string title_, string data_):title(title_), data(data_){} // parametric constructor
};
struct SectionKey
{
	string title;
	BST <ItemKey> * items;

	/*default constructor 
	--> While creating the BST, use this to create a dummy object and pass it for the notFound object. */
	SectionKey()
	{
		title = "noT";
		items = NULL;
	}
	
	SectionKey(const string & title_)
	{
		title = title_;
		ItemKey notFound;
		items = new BST <ItemKey> (notFound);
	}
	// copy constructor dynamically creates the copy of the items tree. new calls clone function of BST class
};

struct SectionKeyAVL
{
	/*default constructor 
	--> While creating the BST, use this to create a dummy object and pass it for the notFound object. */
	string title;
	AVL <ItemKey> * items;

	SectionKeyAVL()
	{
		title = "noT";
		items = NULL;
	}
	SectionKeyAVL(const string & title_)
	{
		title = title_;
		ItemKey notFound;
		items = new AVL <ItemKey> (notFound);
	}
	
};


//my structs should be "comparable"
bool operator!=(const ItemKey & lhs, const ItemKey & rhs) {return (!(lhs.title == rhs.title));}
bool operator<(const ItemKey & lhs, const ItemKey & rhs) {return (rhs.title > lhs.title);}
bool operator>(const ItemKey & lhs, const ItemKey & rhs) {return (rhs.title < lhs.title);}
bool operator==(const ItemKey & lhs, const ItemKey & rhs) {return (lhs.title == rhs.title);}

// for printTree function of BST class
ostream & operator << (ostream & os, const ItemKey & element)   
{
	ostringstream ostr;
	ostr << element.title;
	os << ostr.str();
	return os;
}

bool operator!=(const SectionKey & lhs, const SectionKey & rhs) {return (!(lhs.title == rhs.title));}
bool operator<(const SectionKey & lhs, const SectionKey & rhs) {return (rhs.title > lhs.title);}
bool operator>(const SectionKey & lhs, const SectionKey & rhs) {return (rhs.title < lhs.title);}
bool operator==(const SectionKey & lhs, const SectionKey & rhs) {return (lhs.title == rhs.title);}

ostream & operator << (ostream & os, const SectionKey & element)   
{
	ostringstream ostr;
	ostr << element.title;
	os << ostr.str();
	return os;
}

// for AVL class
bool operator!=(const SectionKeyAVL & lhs, const SectionKeyAVL & rhs) {return (!(lhs.title == rhs.title));}
bool operator<(const SectionKeyAVL & lhs, const SectionKeyAVL & rhs) {return (rhs.title > lhs.title);}
bool operator>(const SectionKeyAVL & lhs, const SectionKeyAVL & rhs) {return (rhs.title < lhs.title);}
bool operator==(const SectionKeyAVL & lhs, const SectionKeyAVL & rhs) {return (lhs.title == rhs.title);}

ostream & operator << (ostream & os, const SectionKeyAVL & element)   
{
	ostringstream ostr;
	ostr << element.title;
	os << ostr.str();
	return os;
}

// main menu: option 3 -> section menu: option 3
void getItemData(const SectionKey & searcedSection, BST <SectionKey> * sectionsTree, AVL <SectionKeyAVL> * sectionsTreeAVL, const SectionKeyAVL & searcedSectionAVL){
	string itemTitle;
	cout << "Enter the title of the item: "; 
	cin >> itemTitle;
	ItemKey item; item.title = itemTitle;

	auto startAVL1 = std::chrono::high_resolution_clock::now();
	ItemKey result2 = sectionsTreeAVL->find(searcedSectionAVL).items->find(item);
	auto endAVL1 = std::chrono::high_resolution_clock::now();
	long long timerAVL = ((endAVL1-startAVL1).count() / 1000.0);

	auto start = std::chrono::high_resolution_clock::now();
	ItemKey result1 = sectionsTree->find(searcedSection).items->find(item);
	auto end = std::chrono::high_resolution_clock::now();
	long long timer = ((end-start).count() / 1000.0);
	
	cout << "[AVL] Elapsed time: " << timerAVL << " microseconds" << endl;
	cout << "[BST] Elapsed time: " << timer << " microseconds" << endl;

	if (result1.title != "noT" && result2.title != "noT" && (result1.title == result2.title)) // check consistency of two trees
	{
		cout << result1.data << endl;
	}
	else 
	{
		cout << "Invalid title." << endl;
	}
}

// main menu: option 3 -> section menu: option 4
void addItem(BST <SectionKey> * sectionsTree, const SectionKey & searcedSection, AVL <SectionKeyAVL> * sectionsTreeAVL, const SectionKeyAVL & searcedSectionAVL){
	string title;
	cout << "Enter a title for the item: ";
	cin >> title;
	ItemKey item; item.title = title;

	if (sectionsTree->find(searcedSection).items->find(item).title == "noT" && sectionsTreeAVL->find(searcedSectionAVL).items->find(item).title == "noT" )
	{
		string data;
		cout << "Enter a description for the item: ";
		cin >> data;
		item.data = data;

		auto startAVL1 = std::chrono::high_resolution_clock::now();
		sectionsTreeAVL->find(searcedSectionAVL).items->insert(item);
		auto endAVL1 = std::chrono::high_resolution_clock::now();
		long long timerAVL = ((endAVL1-startAVL1).count() / 1000.0);
		cout << "[AVL] Elapsed time: " << timerAVL << " microseconds" << endl;

		auto start = std::chrono::high_resolution_clock::now();
		sectionsTree->find(searcedSection).items->insert(item);
		auto end = std::chrono::high_resolution_clock::now();
		long long timer = ((end-start).count() / 1000.0);
		cout << "[BST] Elapsed time: " << timer << " microseconds" << endl;
	
		cout << "The new item \"" << item.title << "\" has been inserted." << endl;
	}
	else
	{
		cout << "Item \"" << title << "\" already exists in the \"" << searcedSection.title << "\"." << endl;
	}
}

// main menu: option 3 -> section menu: option 6
void deleteItem(BST <SectionKey> * sectionsTree, AVL <SectionKeyAVL> * sectionsTreeAVL,  const SectionKey & searchedSection, const SectionKeyAVL & searchedSectionAVL){
	string itemTitle;
	cout << "Enter the title of the item: "; 
	cin >> itemTitle;
	ItemKey item; item.title = itemTitle;
	if (sectionsTree->find(searchedSection).items->find(item).title == itemTitle && sectionsTreeAVL->find(searchedSectionAVL).items->find(item).title == itemTitle)
	{
		auto startAVL1 = std::chrono::high_resolution_clock::now();
		sectionsTreeAVL->find(searchedSectionAVL).items->remove(item);
		auto endAVL1 = std::chrono::high_resolution_clock::now();
		long long timerAVL = ((endAVL1-startAVL1).count() / 1000.0);
		cout << "[AVL] Elapsed time: " << timerAVL << " microseconds" << endl;

		auto start = std::chrono::high_resolution_clock::now();
		sectionsTree->find(searchedSection).items->remove(item);
		auto end = std::chrono::high_resolution_clock::now();
		long long timer = ((end-start).count() / 1000.0);
		cout << "[BST] Elapsed time: " << timer << " microseconds" << endl;
		cout << "The item \"" << itemTitle << "\" has been deleted." << endl;
	}
	else
	{
		cout << "Item \"" << itemTitle << "\" does not exist in the \"" << searchedSection.title << "\"." << endl;
	}
}

// main menu: option 3 -> section menu: option 5
void updateData(const SectionKey & searcedSection, BST <SectionKey> * sectionsTree, AVL <SectionKeyAVL> * sectionsTreeAVL, const SectionKeyAVL & searcedSectionAVL){
	string itemTitle;
	cout << "Enter the title of the item: ";
	cin >> itemTitle;
	ItemKey item; item.title = itemTitle;

	auto startAVL1 = std::chrono::high_resolution_clock::now();
	ItemKey foundAVL = sectionsTreeAVL->find(searcedSectionAVL).items->find(item);
	auto endAVL1 = std::chrono::high_resolution_clock::now();
	long long timerAVL = ((endAVL1-startAVL1).count() / 1000.0);
	cout << "[AVL] Elapsed time: " << timerAVL << " microseconds" << endl;

	auto start = std::chrono::high_resolution_clock::now();
	ItemKey foundBST = sectionsTree->find(searcedSection).items->find(item);
	auto end = std::chrono::high_resolution_clock::now();
	long long timer = ((end-start).count() / 1000.0);
	cout << "[BST] Elapsed time: " << timer << " microseconds" << endl;

	if (foundBST.title == "noT" && foundAVL.title == "noT")
	{
		cout << "Item \"" << itemTitle << "\" does not exist in the \"" << searcedSection.title << "\"." << endl;

	}
	else
	{
		string data;
		cout << "Enter the new information: ";
		cin >>data;
		sectionsTreeAVL->find(searcedSectionAVL).items->remove(item);
		item.data = data;
		sectionsTreeAVL->find(searcedSectionAVL).items->insert(item);

		sectionsTree->find(searcedSection).items->remove(item);
		item.data = data;
		sectionsTree->find(searcedSection).items->insert(item);
		
		cout << "The content " << itemTitle << " has been updated." << endl;

	}
}


void sectionMenu(BST <SectionKey> * sectionsTree, string sectionTitle, AVL <SectionKeyAVL> * sectionsTreeAVL, string sectionTitleAVL){
	cout << "Please enter an input between [1 - 7]:" << endl
         << "1- Display the items [AVL]" << endl
         << "2- Display the items [BST]" << endl
         << "3- Display the information of a item" << endl
         << "4- Add new item" << endl
         << "5- Update the information of a item" << endl
		 << "6- Delete an item" << endl
         << "7- Return to main menu" << endl;
	SectionKey searchedSection; searchedSection.title = sectionTitle;
	SectionKeyAVL searchedSectionAVL; searchedSectionAVL.title = sectionTitleAVL;
	while(true)
	{
		int input;
		cout << "Input: ";
		cin >> input;
		string itemTitle;
		string result;
		switch (input)
		{
			case 1:
				cout << endl;
				cout << "*****" << endl;
				if (sectionsTreeAVL->find(searchedSectionAVL).items->isEmpty() == false)
				{
					sectionsTreeAVL->find(searchedSectionAVL).items->printTree();
				}
				cout << "*****" << endl;
				cout << endl;
		
				break;
			case 2:
				cout << endl;
				cout << "*****" << endl;
				if (sectionsTree->find(searchedSection).items->isEmpty() == false)
				{
					sectionsTree->find(searchedSection).items->printTree();
				}
				cout << "*****" << endl;
				cout << endl;
				break;

			case 3:
				
				getItemData(searchedSection, sectionsTree, sectionsTreeAVL, searchedSectionAVL);
				cout << endl;
				break;

			case 4:
				addItem(sectionsTree, searchedSection, sectionsTreeAVL, searchedSectionAVL);
				cout << endl;
				break;

			case 5:
				updateData(searchedSection, sectionsTree, sectionsTreeAVL, searchedSectionAVL);
				cout << endl;
				break;

			case 6:
				deleteItem(sectionsTree, sectionsTreeAVL, searchedSection, searchedSectionAVL);
				cout << endl;
				break;

			case 7:
				cout << "MENU" << endl;
				cout << "Please enter an input between [1 - 6]: " << endl;
				cout << "1- Display the sections [AVL] " << endl;
				cout << "2- Display the sections [BST] " << endl;
				cout << "3- Select a section " << endl;
				cout << "4- Add new section " << endl;
				cout << "5- Delete a section " << endl;
				cout << "6- Exit " << endl;
				return;

			default:
				cout << "Invalid input!" << endl;
				break;
		}
	}
}


// main menu: option 3 
void selectSection(BST <SectionKey> * sectionsTree, AVL <SectionKeyAVL> * sectionsTreeAVL)
{
	string sectionName;
	cout << "Enter the title of the section: ";
	cin >> sectionName;
	SectionKey section; section.title = sectionName;
	string found1 = sectionsTree->find(section).title;

	SectionKeyAVL sectionAVL; sectionAVL.title = sectionName;
	string found2 = sectionsTreeAVL->find(sectionAVL).title;
	if (found1 == "noT" && found2 == "noT")
	{
		cout << "Invalid title!" << endl;
	}
	else
	{
		cout << endl;
		cout << "Selected section -> " << found1 << endl;
		sectionMenu(sectionsTree, found1, sectionsTreeAVL, found2);
	}

}

// main menu: option 4
void addSection(BST <SectionKey> *& sectionsTree, AVL <SectionKeyAVL> * sectionsTreeAVL){
	string title;
	cout << "Enter a title for the section: ";
	cin >> title;
	SectionKey newSection; newSection.title = title;
	SectionKeyAVL newSectionAVL; newSectionAVL.title = title;
	if (sectionsTree->find(newSection).title == title && sectionsTreeAVL->find(newSectionAVL).title == title)
	{
		cout << "Section \"" << title << "\" already exists." << endl;
	}
	else
	{
		sectionsTree->insert(SectionKey(title));
		sectionsTreeAVL->insert(SectionKeyAVL(title));
		cout << "The new section \"" << title << "\" has been inserted." << endl;
	}
}

// main menu: option 5
void deleteSection(BST <SectionKey> * sectionsTree, AVL <SectionKeyAVL> * sectionsTreeAVL){
	string title;
	cout << "Enter the title of the section: ";
	cin >> title;
	SectionKey newSection; newSection.title = title;
	SectionKeyAVL newSectionAVL; newSectionAVL.title = title;
	if (sectionsTree->find(newSection).title == title && sectionsTreeAVL->find(newSectionAVL).title == title)
	{
		sectionsTree->remove(sectionsTree->find(newSection));
		sectionsTreeAVL->remove(sectionsTreeAVL->find(newSectionAVL));
		cout << "The section has been deleted." << endl;
	}
	else
	{
		cout << "Section \"" << title << "\" does not exist." << endl;
	}
}



void showChronoInfoBST(SectionKey section, long long totalTime){
	cout << "Section \"" << section.title  <<"\" has been inserted into the BST notebook." << endl;
	cout << "[BST] Elapsed time: " << totalTime << " microseconds" << endl;
}

void showChronoInfoAVL(SectionKeyAVL section, long long totalTime){
	cout << "Section \"" << section.title  <<"\" has been inserted into the AVL notebook." << endl;
	cout << "[AVL] Elapsed time: " << totalTime << " microseconds" << endl;
}


int main(){
	cout << "Welcome to the Notebook!" << endl;
	cout << endl;
	ifstream in;
	string fileName =  "data.txt";
	in.open(fileName.c_str());
	string line;
	string sectionTitle, itemLine, itemTitle, itemInfo;
	SectionKey notFoundSection;
	SectionKeyAVL notFoundSectionAVL;
	ItemKey notFoundItem;
	// form tree dynamically
	BST <SectionKey> * sectionsTree = new BST <SectionKey> (notFoundSection); 
	AVL <SectionKeyAVL> * sectionsTreeAVL = new AVL <SectionKeyAVL> (notFoundSectionAVL);
	ItemKey newItemKey;
	SectionKey newSection;
	SectionKeyAVL newSectionAVL;

	bool chorono_new_sec = false;
	bool endOfsections = false;
	if (!in.fail())
	{
		long long totalTime;
		long long totalTimeAVL;
		bool treeCreated = false;
		while (getline(in, line))
		{
			if (line != "\r" && line != "") {
				istringstream ss(line);
				endOfsections = false;
				if (line[0] != '-') // found a section title
				{
					if (chorono_new_sec)
					{
						showChronoInfoAVL(newSectionAVL, totalTimeAVL);
						showChronoInfoBST(newSection, totalTime);
						cout << endl;
					}
					
					ss >> sectionTitle;
					chorono_new_sec =true;
					totalTime = 0;
					totalTimeAVL = 0;
					newSection.title = sectionTitle;
					newSectionAVL.title = sectionTitle;
					auto startAVL1 = std::chrono::high_resolution_clock::now();
					// copy constructor of SectionKey and SectionKeyAVL are used for insertion input.
					sectionsTreeAVL->insert(SectionKeyAVL(sectionTitle));
					auto endAVL1 = std::chrono::high_resolution_clock::now();
					long long timerAVL1 = ((endAVL1-startAVL1).count() / 1000.0);
					totalTimeAVL += timerAVL1;

					auto start1 = std::chrono::high_resolution_clock::now();
					sectionsTree->insert(SectionKey(sectionTitle));
					auto end1 = std::chrono::high_resolution_clock::now();
					long long timer1 = ((end1-start1).count() / 1000.0);
					totalTime += timer1;
				
				}
				else if (line[0] == '-') // add items
				{
					getline(ss,itemLine);
					itemLine = itemLine.substr(1);
					int dashIdx = itemLine.find("-");
					itemTitle = itemLine.substr(0, dashIdx);
					itemInfo = itemLine.substr(dashIdx+1, itemLine.length()-dashIdx-1);
					newItemKey.title = itemTitle;
					newItemKey.data = itemInfo;

					auto startAVL2 = std::chrono::high_resolution_clock::now();
					sectionsTreeAVL->find(newSectionAVL).items->insert(newItemKey);
					auto endAVL2 = std::chrono::high_resolution_clock::now();
					long long timerAVL2 = ((endAVL2-startAVL2).count() / 1000.0);
					totalTimeAVL += timerAVL2;

					auto start2 = std::chrono::high_resolution_clock::now();
					sectionsTree->find(newSection).items->insert(newItemKey);
					auto end2 = std::chrono::high_resolution_clock::now();
					long long timer2 = ((end2-start2).count() / 1000.0);
					totalTime += timer2;

					endOfsections = true;
				}
			}
			
		}
		if (endOfsections)
		{
			cout << "Section \"" << newSection.title  <<"\" has been inserted into the AVL notebook." << endl;
			cout << "[AVL] Elapsed time: " << totalTimeAVL << " microseconds" << endl;
			cout << "Section \"" << newSection.title  <<"\" has been inserted into the BST notebook." << endl;
			cout << "[BST] Elapsed time: " << totalTime << " microseconds" << endl;
			cout << endl;
		}

	}
	else
	{
		cout << "cannot found the file!" << endl;
	}
	in.close();



	cout << "MENU" << endl;
	cout << "Please enter an input between [1 - 6]: " << endl;
	cout << "1- Display the sections [AVL] " << endl;
	cout << "2- Display the sections [BST] " << endl;
	cout << "3- Select a section " << endl;
	cout << "4- Add new section " << endl;
	cout << "5- Delete a section " << endl;
	cout << "6- Exit " << endl;
	while(true)
	{
		int input;
		cout << "Input: ";
		cin >> input;
		switch (input)
		{
			case 1:
				cout << endl;
				cout << "*****" << endl;
				if (sectionsTreeAVL->isEmpty() == false)
				{
					sectionsTreeAVL->printTree();
				}
				cout << "*****" << endl;
				cout << endl;
				
				break;
			case 2:
				cout << endl;
				cout << "*****" << endl;
				if (sectionsTreeAVL->isEmpty() == false){
					sectionsTree->printTree();
				}
				cout << "*****" << endl;
				cout << endl;
				break;

			case 3:
				selectSection(sectionsTree, sectionsTreeAVL);
				break;

			case 4:
				addSection(sectionsTree, sectionsTreeAVL);
				cout << endl;
				break;

			case 5:
				deleteSection(sectionsTree, sectionsTreeAVL);
				cout << endl;
				break;

			case 6:
				exit(0);
				break;

			default:
				cout << "Invalid input!" << endl;
				break;
		}
	}
		
	return 0;
}
