// Ceren Arkac ,28269, CS 300, HW4
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include "strutils.h"
using namespace std;

struct PhoneBookItem
{
	string name;
	string surname;
	string phoneNum;
	string city;
	string fullName;

	PhoneBookItem(){}

	PhoneBookItem(string name_, string surname_, string phoneNum_, string city_):name(name_), surname(surname_), phoneNum(phoneNum_), city(city_){
		fullName = name + " " + surname;
	}

};


bool operator<(const PhoneBookItem & lhs, const PhoneBookItem & rhs) {return (rhs.fullName > lhs.fullName);}
bool operator>(const PhoneBookItem & lhs, const PhoneBookItem & rhs) {return (rhs.fullName < lhs.fullName);}
bool operator==(const PhoneBookItem & lhs, const PhoneBookItem & rhs) {return (lhs.fullName == rhs.fullName);}
bool operator>=(const PhoneBookItem & lhs, const PhoneBookItem & rhs){return ! (lhs < rhs);}
bool operator!=(const PhoneBookItem & lhs, const PhoneBookItem & rhs) {return (!(lhs.fullName == rhs.fullName));}
bool operator==(const PhoneBookItem & lhs, const string & rhs) {return (lhs.fullName == rhs);}
bool operator<=(const PhoneBookItem & lhs, const PhoneBookItem & rhs){return ! (lhs > rhs);}


/* assisting function for testing purposes*/
ostream & operator << (ostream & os, const PhoneBookItem & element)   
{
	ostringstream ostr;
	ostr << element.fullName << " "<< element.phoneNum << " " << element.city;
	os << ostr.str();
	return os;
}

/***sorting algorithms***/

// insertion sort
template <class Comparable>
void insertionSort (vector <Comparable> & a)
{
	int j;
	for (int p = 1; p < a.size(); p++)
	{
		Comparable tmp = a[p];
		for (j = p; j > 0 && tmp < a[j - 1]; j--)
			a[j] = a[j-1];
		a[j] = tmp;
	}
}

// quick sort

template <class Comparable>
void insertionSort(vector<Comparable>& a, int left, int right) {
	for (int p = left + 1; p <= right; p++) {
		Comparable tmp = a[p];
		int j;
		for (j = p; j > left && tmp < a[j - 1]; j--)
			a[j] = a[j - 1];
		a[j] = tmp;
	}
}

template <class Comparable>
void quicksort(vector<Comparable> & a, int left, int right)
{
	if (left + 10 <= right)
	{
		Comparable pivot = median3(a, left, right);
		int i = left, j = right - 1;
		for (;;)
		{
			while ( a[++i] < pivot){}

			while (pivot < a[--j]){}

			if (i < j)
				my_swap(a[i], a[j]);
			else
				break;
		}

		my_swap(a[i], a[right - 1]);   // Restore pivot

		quicksort(a, left, i - 1);       // Sort small elements
		quicksort(a, i + 1, right);    // Sort large elements
	}
	else  // Do an insertion sort on the subarray
		insertionSort(a, left, right);
}

/**
* Quicksort algorithm (driver).
*/
template <class Comparable>
void quicksort(vector<Comparable> & a)
{
	quicksort(a, 0, a.size()-1);
} 

/**
* Standard swap
*/
template <class Comparable>
inline void my_swap( Comparable & obj1, 
				 Comparable & obj2 )
{
	Comparable tmp = obj1;
	obj1 = obj2;
	obj2 = tmp;
}

/** Return median of left, center, and right.
*   Order these and hide the pivot.
*/
template <class Comparable>
const Comparable & median3(vector<Comparable> & a, int left, int right)
{
	int center = (left + right) / 2;
	if (a[center] < a[left])
		my_swap(a[left], a[center]);
	if (a[right] < a[left])
		my_swap(a[left], a[right]);
	if (a[right] < a[center])
		my_swap(a[center], a[right]);

	// Place pivot at position right - 1
	my_swap(a[center], a[right - 1]);
	return a[right - 1];
}


template <class Comparable>
void mergeSort( vector<Comparable> & a )
{
    mergeSort(a, 0, a.size()-1);
}

/*

- Internal method that makes recursive calls.
- a is an array of Comparable items.
- tmpArray is an array to place the merged result.
- left is the left-most index of the subarray.
- right is the right-most index of the subarray.
*/
template <class Comparable>
void mergeSort( vector<Comparable> & a, int left, int right)
{
	if (left < right)
	{
		int center = (left + right) / 2;
		mergeSort(a, left, center);
		mergeSort(a, center + 1, right);
		merge(a, left, center + 1, right);
	 }

	 else
	 {
		return;
	 }
}

template <class Comparable>
void merge(vector<Comparable> & a, int leftPos, int rightPos, int rightEnd)
{
	int leftEnd = rightPos - 1;
	if (a[leftEnd] <= a[rightPos]) // already sorted
	{
		return;
	}

	while (leftPos <= leftEnd && rightPos <= rightEnd)
	{
		if (a[leftPos] <= a[rightPos])
		{
			leftPos++;
		}
		else
		{
			Comparable value = a[rightPos];
			int index = rightPos;

			while (index != leftPos)
			{
				a[index] = a[index-1];
				index--;
			}
			a[leftPos] = value;

			leftPos++;
			leftEnd++;
			rightPos++;
		}
	}
}

// heap sort
inline int leftChild (int i)
{
	return 2*i+1;
}

template <class Comparable>  
// for deleteMax
// a is the array, i is the position to percolate down from
// n is the logical size of the array
void percDown(vector<Comparable> & a, int i, int n)
{
	int child;
	Comparable tmp;

	for (tmp=a[i] ; leftChild(i) < n; i = child)
	{
		child = leftChild(i);
		if (child != n-1 && a[child] < a[child+1])
			child++;
		if (a[child] > tmp)
			a[i] = a[child];
		else
			break;
	} 
	a[i] = tmp;
}



template <class Comparable>
void heapsort(vector<Comparable> & a)
{
	// buildHeap
	for (int i = a.size()/2; i >=0; i--)
		percDown(a, i, a.size());

	// sort
	for (int j = a.size()-1; j >0; j--)
	{
		my_swap(a[0], a[j]);    // swap max to the last pos.
		percDown(a, 0, j); // re-form the heap
	}
}





/***searching algorithms***/

// sequential search
vector <PhoneBookItem> sequentialSearch(const vector <PhoneBookItem> & vec, const string & query){
	vector <PhoneBookItem> results;
	string partialQuery;
	if (query.find(" ") == string::npos) // Partial Contact Name Search
	{
		for (int i = 0; i < vec.size(); i++)
		{
			partialQuery = vec[i].name.substr(0, query.length());
			if (partialQuery == query)
			{
				results.push_back(vec[i]);
			}
		}
	}
	else // Full Contact Name Search
	{
		for (int i = 0; i < vec.size(); i++)
		{
			if (vec[i] == query)
			{
				results.push_back(vec[i]);
			}
		}
	}
	return results;
}

// binary search
// I used cs201 codes
 int bsearch(const vector<PhoneBookItem>& vec, const string & query, bool findFirst){ // desingned to be used in partial name searches
// pre: list.size() == # elements in list
// post: returns index of key in list, -1 if key not found
    int low = 0;                   // leftmost possible entry
    int high = vec.size()-1;      // rightmost possible entry
    int mid;                       // middle of current range
	int result = -1;
    while (low <= high){   
		mid = (low + high)/2;
		string partialQuery = vec[mid].name.substr(0, query.length());
		if (partialQuery == query){       
			// found key but it may not be exactly the first occurence of the query in the vector. 
			// I should find the first and last occurrences (as indexes) and then print the between.
				result = mid;
				if (findFirst)  // continue to search towards left to find the first occurence
				{
					high = mid-1;
				}
				else // continue to search towards right to find the first occurence
				{
					low = mid+1;
				}
		}
		else if (partialQuery < query)   // key in upper half
           low = mid + 1;
        else                        // key in lower half
           high = mid - 1;
    }
    return result;                      // not in list
} 

 int bsearch(const vector<PhoneBookItem>& vec, const string & query){ // overloaded to be used in full name searches
// pre: list.size() == # elements in list
// post: returns index of key in list, -1 if key not found
    int low = 0;                   // leftmost possible entry
    int high = vec.size()-1;      // rightmost possible entry
    int mid;                       // middle of current range
    while (low <= high){   
		mid = (low + high)/2;
		
		if (vec[mid].fullName == query){       
			return mid;
		}
		else if (vec[mid].fullName < query)   // key in upper half
           low = mid + 1;
        else                        // key in lower half
           high = mid - 1;
    }
    return -1;                      // not in list
} 




int main(){

	string fileName;
	cout << "Please enter the contact file name: ";
	cin >> fileName;

	// read the input file
	ifstream in;
	string line;
	in.open(fileName.c_str());
	string name, surname, phoneNum, city;
	vector<PhoneBookItem> vec1;
	if (!in.fail()){

		while (getline(in, line))
		{
			if (line != "\r" && line != "") {
				istringstream ss(line);
				ss >> name >> surname >> phoneNum >> city;
				ToUpper(name);
				ToUpper(surname);
				PhoneBookItem itemX(name, surname, phoneNum, city);
				vec1.push_back(itemX);
			}
		}
	}
	in.close();
	// load the PhoneBook into different vectors i.e., 4 copy of the same vector) where I am going to apply a sorting algorithm on each one
	vector<PhoneBookItem> vec2(vec1);
	vector<PhoneBookItem> vec3(vec1);
	vector<PhoneBookItem> vec4(vec1);



	// ask for a search query
	string query;
	cout << "Please enter the word to be queried  :" << endl; // contact name
	cin.get();
	getline(cin, query);
	string realQuery = query;
	ToUpper(query);
	cout << endl; cout << endl;
	cout << "Sorting the vector copies" << endl;
	cout << "======================================" << endl;
	// sort all (4) the vectors according to the sorting algorithms

	// apply quick sort and measure its running time
	auto quickRTstart = std::chrono::high_resolution_clock::now();
	quicksort(vec1);
	auto quickRTend = std::chrono::high_resolution_clock::now();
	long long timerquickRT = ((quickRTend-quickRTstart).count() / 1.0);

	// apply insertion sort and measure its running time

	auto InsRTstart = std::chrono::high_resolution_clock::now();
	insertionSort(vec2);
	auto InsRTend = std::chrono::high_resolution_clock::now();
	long long timerInsRT = ((InsRTend-InsRTstart).count() / 1.0);
	
	// apply merge sort and measure its running time
	auto mergeRTstart = std::chrono::high_resolution_clock::now();
	mergeSort(vec3);
	auto mergeRTend = std::chrono::high_resolution_clock::now();
	long long timermergeRT = ((mergeRTend-mergeRTstart).count() / 1.0);

	// apply heap sort and measure its running time
	auto heapRTstart = std::chrono::high_resolution_clock::now();
	heapsort(vec4);
	auto heapRTend = std::chrono::high_resolution_clock::now();
	long long timerheapRT = ((heapRTend-heapRTstart).count() / 1.0);

	cout << "Quick Sort Time: " << timerquickRT << endl;
	cout << "Insertion Sort Time: " << timerInsRT << endl;
	cout << "Merge Sort Time: " << timermergeRT << endl;
	cout << "Heap Sort Time: " << timerheapRT << endl;
	cout << endl;
	cout << endl;
	
	cout << "Searching for " << realQuery << endl;
	cout << "======================================" << endl;

	// do binary search and measure it
	int N1 = 100; // if cannot be measured, try N = 1000
	auto binaryRTstart = std::chrono::high_resolution_clock::now();
	int firstOcc, lastOcc, found;
	bool fullNameSearch = false;
	for (int i = 0; i < N1; i++){
	
		if (query.find(" ") == string::npos){ // Partial Contact Name Search
			fullNameSearch = false;
			firstOcc = bsearch(vec2, query, true);
			lastOcc = bsearch(vec2, query, false);
			
		}
		else // FullName Search
		{
			fullNameSearch = true;	
			found = bsearch(vec2, query);
		}
	}

	auto binaryRTend = std::chrono::high_resolution_clock::now();
	long long timerbinaryRT = ((binaryRTend-binaryRTstart).count() / 100.0);

	if (fullNameSearch)
	{
		if (found == -1)
		{
			cout << query << " does NOT exist in the dataset" << endl;
		}
		else
		{
			cout << vec2[found] << endl;
		}
	}
	else
	{
		if (firstOcc != -1 && lastOcc != -1)
		{
			for (int i = firstOcc; i <= lastOcc; i++)
			{
				cout << vec2[i] << endl;
			}
		}
		else if (firstOcc == -1 && lastOcc == -1)
		{
			cout << query << " does NOT exist in the dataset" << endl;
		}
		else
		{
			if (firstOcc == -1)
			{
				cout << vec2[firstOcc] << endl;
			}
			else
			{
				cout << vec2[lastOcc] << endl;
			}
		}
	}
	
	cout << "Binary Search Time: " << timerbinaryRT << " Nanoseconds" << endl;
	cout << endl;

	cout << "Search results for Sequential Search: " << endl;

	// do sequential search and measure it
	int N2 = 100; // if cannot be measured, try N = 1000
	auto sequenRTstart = std::chrono::high_resolution_clock::now();
	vector <PhoneBookItem> results;
	for (int i = 0; i < N2; i++)
	{
		results = sequentialSearch(vec2, query);
	}
	
	auto sequenRTend = std::chrono::high_resolution_clock::now();
	long long timersequenRT = ((sequenRTend-sequenRTstart).count() / 100.0);

	if (results.size() == 0)
	{
		cout << query << " does NOT exist in the dataset" << endl;
	}
	else
	{
		for (int i = 0; i < results.size(); i++)
		{
			cout << results[i] << endl;
		}
	}
	cout << endl;

	cout << "Sequential Search Time: " << timersequenRT << " Nanoseconds" << endl;
	cout << endl;

	cout << "SpeedUp between Search Algorithms"  << endl;
	cout << "======================================" << endl;
	cout << "(Sequential Search/ Binary Search) SpeedUp = " << (double)timersequenRT / (double)timerbinaryRT << endl;

	cout << endl;

	cout << "SpeedUps between Sorting Algorithms" << endl;
	cout << "======================================" << endl;
	cout << "(Insertion Sort/ Quick Sort) SpeedUp = " << (double)timerInsRT / (double)timerquickRT << endl;
	cout << "(Merge Sort / Quick Sort) SpeedUp = " << (double)timermergeRT / (double)timerquickRT << endl;
	cout << "(Heap Sort / Quick Sort) SpeedUp = " << (double)timerheapRT / (double)timerquickRT << endl;
	

	return 0;
}
