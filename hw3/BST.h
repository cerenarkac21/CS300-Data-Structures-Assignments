// Ceren Arkac ,28269, CS 300, HW3
#ifndef _BST_H
#define _BST_H
#pragma comment(linker, "/HEAP:10000000")
#pragma comment(linker, "/STACK:10000000")
template <class Comparable>
class BST;

template <class Comparable>
class BinaryNode
{
	Comparable element;
	BinaryNode  *left;
	BinaryNode  *right;

	BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt): element(theElement), left(lt), right(rt) {}

	friend class BST<Comparable>;
};

template <class Comparable>
class BST
{
public:
	BST()
	{
		root = NULL;
	}
	explicit BST(const Comparable & notFound)
	{
		ITEM_NOT_FOUND = notFound;
		root = NULL;
	}
	BST(const BST <Comparable> & rhs){  // bak buraya comparable yazman lazim
		root = rhs.clone(rhs.root);
		ITEM_NOT_FOUND = rhs.ITEM_NOT_FOUND;
	}
	
	const BST <Comparable> & operator=( const BST <Comparable> & rhs ){
		if (this != &rhs)
		{
			makeEmpty();
			root = rhs.clone(rhs.root);
			ITEM_NOT_FOUND = rhs.ITEM_NOT_FOUND;
		}
		return *this;
	}

	~BST(){
		makeEmpty();
	}

	void printTree() const{
		if(isEmpty())
            cout << "Empty tree" << endl;
        else
            printTree(root);
	}

	bool isEmpty() const
	{
		if (root == NULL)
		{
			return true;
		}
		else		{			return false;		}
	}

	void insert(const Comparable & x)
    {
        insert(x, root);
    }

	void remove (const Comparable & x)
    {
		remove(x, root);
    }

    void makeEmpty()
    {
            makeEmpty(root);
    }

	const Comparable & find(const Comparable & x) const
    {
		return elementAt(find(x, root));
    }

	const Comparable & findMin() const
    {
        return elementAt(findMin(root));
    }

	const Comparable & findMax() const
    {
        return elementAt(findMax(root));
    }
	
private:
	BinaryNode<Comparable> *root;
	Comparable ITEM_NOT_FOUND;
	
    BinaryNode<Comparable> * clone( BinaryNode<Comparable> * t ) const
    {
        if ( t == NULL )
            return NULL;
        else
            return new BinaryNode<Comparable> (t->element, clone(t->left), clone(t->right));
    }

	void remove(const Comparable & x, BinaryNode<Comparable> * & t) const
    {
        if(t == NULL)
            return;   // Item not found; do nothing
        if(x < t->element)
            remove(x, t->left);
        else if(t->element < x){
            remove(x, t->right);
		}
		else if(t->left != NULL && t->right != NULL) // Two children
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else // one or no children
        {
            BinaryNode<Comparable> *oldNode = t;
			t = ( t->left != NULL ) ? t->left : t->right;
            delete oldNode;
        }
    }    
	        
    void insert(const Comparable & x, BinaryNode<Comparable> * & t ) const
    {
        if( t == NULL ) //  create a new node at the right place
            t = new BinaryNode<Comparable>( x, NULL, NULL );
        else if( x < t->element )
            insert( x, t->left );  // insert at the left or 
        else if( t->element < x )
            insert( x, t->right );  // right subtree
        else
            ;  // Duplicate; do nothing
    }

	        
    void makeEmpty( BinaryNode<Comparable> * & t ) const
    {
        if( t != NULL )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = NULL;
    }

	void printTree( BinaryNode<Comparable> * t) const
    {
        if (t != NULL)
        {
            printTree(t->left);
            cout << t->element << endl;
            printTree(t->right);
        }
    }

	BinaryNode<Comparable> * find( const Comparable & x, BinaryNode<Comparable> * t ) const
	{
        if (t == NULL)
            return NULL;
        else if(x < t->element)
            return find(x, t->left);
        else if(t->element < x)
            return find(x, t->right);
        else
            return t;    // Match
	}

	
    const Comparable & elementAt(BinaryNode<Comparable> *t)const
    {
        return t == NULL ? ITEM_NOT_FOUND : t->element;
    }
        
	BinaryNode<Comparable> * findMin(BinaryNode<Comparable> *t)const
    {
        if(t == NULL)
            return NULL;
        if(t->left == NULL)
            return t;
        return findMin(t->left);
    }

	BinaryNode<Comparable> * findMax(BinaryNode<Comparable> *t)const
    {
        if(t != NULL)
            while(t->right != NULL)
                t = t->right;
        return t;
    }

};

#endif