// // Ceren Arkac ,28269, CS 300, HW3
#ifndef _SEP_CHAIN_HASHTABLE_H
#define _SEP_CHAIN_HASHTABLE_H
#include <iostream>
#include <string>
#include <vector>
#include <string>


template <class HashedObj>
class ListNode;

template <class HashedObj>
class ListItr;     // Incomplete declaration.

template <class HashedObj>
class List;     // Incomplete declaration.

template <class HashedObj>
class HashTable
{
public:

	HashTable(const HashedObj & notFound, int size = 50):ITEM_NOT_FOUND(notFound), theLists(nextPrime(size)){numOfEntries = 0;}
	HashTable(const HashTable & rhs): ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND), theLists(rhs.theLists) {numOfEntries = rhs.numOfEntries}

	~HashTable()
	{
        makeEmpty();  // Get rid of all list nodes
    }

	int getNumOfEntries(){
		return numOfEntries;
	}

	double getLoadFactor(){
		return (double(getNumOfEntries())/theLists.size());
	}

    const HashedObj & find(const HashedObj & x) const
	{
        ListItr<HashedObj> itr;
        // locate the approriate list and search there
        itr = theLists[hash1(x, theLists.size())].find(x);
        // retrieve from the located position
        if (itr.isPastEnd())
	  		return ITEM_NOT_FOUND;
	
		return itr.retrieve();
	}


    void makeEmpty()
	{
        for( int i = 0; i < theLists.size(); i++)
            theLists[i].makeEmpty(); 
				// destroy the lists but not the vector!
		numOfEntries = 0;
    }

    void insert(const HashedObj & x)
	{
        // hash the given object and locate the list it should be on 
        List<HashedObj> & whichList = theLists[hash1(x, theLists.size())];
        // locate the object in the list (using List’s find)
        ListItr<HashedObj> itr = whichList.find(x);

        // insert the new item at the head of the list if not found!
        if (itr.isPastEnd()){
			whichList.insert(x, whichList.zeroth());
			if(double(++numOfEntries) / double(theLists.size()) > double(0.9))
			{
				rehash();
			}
		}
		else
		{
			return;
		}
			
    }

	int numOfUniqueWords(){
		int count = 0;
		for (int i = 0; i < theLists.size(); i++)
		{
			ListItr <HashedObj> itr = theLists[i].first();
			for ( ; !itr.isPastEnd(); itr.advance()){
				count+=1;
			}
		}
		return count;
	}

    void remove(const HashedObj & x)
	{
        // remove from the appropriate list
        theLists[hash1(x,theLists.size())].remove(x);
		numOfEntries--;
    }


    const HashTable & operator=(const HashTable & rhs){
		if (this != &rhs)
		{
			makeEmpty();
			for (int i = 0; i < rhs.size(); i++)
			{
				theLists[i] = rhs[i];
			}
			ITEM_NOT_FOUND = rhs.ITEM_NOT_FOUND;
			numOfEntries = rhs.numOfEntries;
		}
		return *this;
	}

private:
	vector<List<HashedObj>> theLists;   // The array of Lists
	const HashedObj ITEM_NOT_FOUND;
	friend class ListItr<HashedObj>;
	friend class List<HashedObj>;
	friend class ListNode<HashedObj>;
	int numOfEntries;

	int elementCount;
	bool isPrime(int n)
	{
		if (n == 2 || n == 3)
			return true;

		if (n == 1 || n % 2 == 0)
			return false;

		for (int i = 3; i * i <= n; i += 2)
				if (n % i == 0)
					return false;

		return true;
	}

	int nextPrime(int n)
	{
		if (n % 2 == 0)
			n++;

        for ( ; !isPrime(n); n += 2)
            ;

         return n;
	}

	void rehash()
	{
		vector<List<HashedObj>> oldLists = theLists;
		// Create new double-sized, empty table
		int oldSize = theLists.size();
		theLists.resize(nextPrime(2 * theLists.size()));
		makeEmpty(); // destroy the lists but not the vector!

		for (int i = 0; i < oldLists.size(); i++)
		{
			ListItr <HashedObj> itr = oldLists[i].first();
			for ( ; !itr.isPastEnd(); itr.advance()){
				insert(itr.retrieve());
			}
		}
		cout << "rehashed..." << endl;
		cout << "previous table size: " << oldSize << ", new table size: " << theLists.size() << ", current unique word count " << numOfEntries+1 << ", current load factor: " << getLoadFactor() << endl;
	}
	
};


int hash2(const string & key, int tableSize){
	int hashVal = 0;
  
    for (int i = 0; i < key.length();i++) 
	  hashVal = 37 * hashVal + key[i];

    hashVal = hashVal % tableSize;

    if (hashVal < 0) 
	  hashVal = hashVal + tableSize;

   return(hashVal);
}


template <class HashedObj>
class ListNode
{
    ListNode(const HashedObj & theElement = HashedObj(), ListNode * n = NULL)
        : element(theElement), next(n) {}  // Constructor 

    HashedObj   element;
    ListNode *next;

    friend class List<HashedObj>;
    friend class ListItr<HashedObj>;
};

template <class HashedObj>
class ListItr
{
    public:
        ListItr() : current(NULL) {
			INF = HashedObj();
		}

        bool isPastEnd() const{  // check if current is null
			return current == NULL;
		}

        void advance(){  // move to the next node
			if (!isPastEnd()){
				current = current->next;
			}
		}
        const HashedObj & retrieve() const  
        {
			if (!isPastEnd())
				return current->element;
			else {
				return INF;
			} 
		}
		

    private:
        ListNode<HashedObj> *current;    // Current position
		HashedObj INF;
        ListItr(ListNode<HashedObj> *theNode)
              	:current(theNode) {}

        friend class List<HashedObj>;    // Grant access to constructor

};

template <class HashedObj>
class List
{
public:
	List()
	{
		header = new ListNode<HashedObj>;
	}

    List(const List & rhs)
	{
		header = new ListNode<HashedObj>;
		*this = rhs;  // Deep Copy
    }

    ~List()
	{
        makeEmpty();  // Get rid of all list nodes
        delete header;  // then get rid of the header
    }

    bool isEmpty() const
	{
	// see if the header points to NULL
		return header->next == NULL;
    }

    void makeEmpty()
	{
		while (!isEmpty()){
			remove(first().retrieve());
		}
	}

    ListItr<HashedObj> zeroth() const
	{
		return ListItr<HashedObj>(header);
	}

    ListItr<HashedObj> first() const
	{
		return ListItr<HashedObj>(header->next);
	}

    void insert(const HashedObj & x, const ListItr<HashedObj> & p)
	{
		if (p.current != NULL){
			p.current->next = new ListNode<HashedObj>(x, p.current->next);
		}
	}

    ListItr<HashedObj> find(const HashedObj & x) const
	{
		ListNode<HashedObj> *itr = header->next; // Initialize
		while (itr != NULL && itr->element != x){
			itr = itr->next;
		}
		return ListItr<HashedObj>(itr);
	}

    ListItr <HashedObj> findPrevious(const HashedObj & x) const
	{
		ListNode<HashedObj> *itr = header;
		while ( itr->next != NULL && itr->next->element != x){
			itr = itr->next;
		}
		return ListItr<HashedObj>(itr);
	}

    void remove(const HashedObj & x)
	{
		ListItr<HashedObj> p = findPrevious(x); // Locate previous of x, if any

        if (p.current->next != NULL)
        {
            ListNode<HashedObj> *oldNode = p.current->next;
            p.current->next = p.current->next->next;  // Bypass deleted node
            delete oldNode;
        }

	}
    
	const List<HashedObj> & operator=(const List<HashedObj> & rhs)
	{
		if (this != &rhs)
        {
            makeEmpty();
            ListItr<HashedObj> ritr = rhs.first();
            ListItr<HashedObj> itr = zeroth();
            for ( ; !ritr.isPastEnd(); ritr.advance(), itr.advance())
                insert(ritr.retrieve(), itr);
        }
        return *this;
	}
        


private:
	ListNode<HashedObj> *header;
};




#endif



