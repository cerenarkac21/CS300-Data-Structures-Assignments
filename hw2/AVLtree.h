// Ceren Arkac ,28269, CS 300, HW2
#ifndef _AVL_H
#define _AVL_H
#pragma comment(linker, "/STACK:2000000")
template <class Comparable>
class AVL;

template <class Comparable>
class AvlNode
{
        Comparable 	element;
        AvlNode *left;
        AvlNode *right;
		int height;

        AvlNode(const Comparable & theElement, AvlNode *lt, AvlNode *rt, int h = 0)
            : element(theElement), left(lt), right(rt), height(h) {}		

        friend class AVL<Comparable>;
};


template <class Comparable>
class AVL
{
public:
	AVL()
	{
		root = NULL;
	}
	explicit AVL(const Comparable & notFound)
	{
		ITEM_NOT_FOUND = notFound;
		root = NULL;
	}
	AVL(const AVL <Comparable> & rhs){  // bak buraya comparable yazman lazim
		root = rhs.clone(rhs.root);
		ITEM_NOT_FOUND = rhs.ITEM_NOT_FOUND;
	}
	
	const AVL <Comparable> & operator=(const AVL <Comparable> & rhs ){
		if (this != &rhs)
		{
			makeEmpty();
			root = rhs.clone(rhs.root);
			ITEM_NOT_FOUND = rhs.ITEM_NOT_FOUND;
		}
		return *this;
	}

	~AVL(){
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
		if (root == NULL){return true;}
		else{return false;}
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
	AvlNode <Comparable> *root;
	Comparable ITEM_NOT_FOUND;
	
    AvlNode <Comparable> * clone(AvlNode<Comparable> * t) const
    {
        if ( t == NULL )
            return NULL;
        else
            return new AvlNode<Comparable> (t->element, clone(t->left), clone(t->right));
    }

	void insert(const Comparable & x, AvlNode <Comparable> * & t) const
	{
		   if (t == NULL)
			   t = new AvlNode <Comparable> (x, NULL, NULL);

		   else if (x < t->element) 
		   {
			   // X should be inserted to the left tree!
			   insert(x, t->left);
           
		// Check if the left tree is out of balance (left subtree grew in height!)
			   if (height( t->left) - height(t->right) == 2 )

					if (x < t->left->element)  // X was inserted to the left-left subtree!
						 rotateWithLeftChild(t);
					else			     // X was inserted to the left-right subtree!
						 doubleWithLeftChild(t);
		    }
			else if(t->element < x)
			{    // Otherwise X is inserted to the right subtree
					insert(x, t->right);
					if ( height(t->right) - height(t->left) == 2)
			// height of the right subtree increased
						if (t->right->element < x)
		     			// X was inserted to right-right subtree
							rotateWithRightChild(t);
						else // X was inserted to right-left subtree
							doubleWithRightChild(t);
			}
			else
				;  // Duplicate; do nothing
            
			// update the height the node
			t->height = max(height(t->left), height(t->right)) + 1;
	}

    void makeEmpty(AvlNode<Comparable> * & t) const
    {
        if( t != NULL )
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = NULL;
    }

	void printTree(AvlNode<Comparable> * t) const
    {
        if (t != NULL)
        {
            printTree(t->left);
            cout << t->element << endl;
            printTree(t->right);
        }
    }

	AvlNode<Comparable> * find( const Comparable & x, AvlNode<Comparable> * t ) const
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

	
    const Comparable & elementAt(AvlNode<Comparable> *t) const
    {
        return t == NULL ? ITEM_NOT_FOUND : t->element;
    }
        
	AvlNode<Comparable> * findMin (AvlNode<Comparable> *t)const
    {
        if(t == NULL)
            return NULL;
        if(t->left == NULL)
            return t;
        return findMin(t->left);
    }

	AvlNode<Comparable> * findMax(AvlNode<Comparable> *t)const
    {
        if(t != NULL)
            while(t->right != NULL)
                t = t->right;
        return t;
    }
	
	void remove(const Comparable & x, AvlNode <Comparable> * & t) const
	{
        if(t == NULL)
            return;   // Item not found; do nothing
        if(x < t->element)
            remove(x, t->left);
        else if(t->element < x)
            remove(x, t->right);
		  else if(t->left != NULL && t->right != NULL) // Two children
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else // one or no children
        {
            AvlNode<Comparable> *oldNode = t;
            t = (t->left != NULL) ? t->left : t->right;
            delete oldNode;
			
        }

		if (t == NULL){
			 return;
		}

		if (height( t->left) - height(t->right) == 2){
			if(height(t->left->left) >= height(t->left->right)){
				rotateWithLeftChild(t);
			}
			else
			{
				doubleWithLeftChild(t);
			}
		}
		else if (height(t->right) - height(t->left) == 2)
		{
			if(height(t->right->right) >= height(t->right->left)){
				rotateWithRightChild(t);
			}
			else
			{
				doubleWithRightChild(t);
			}
		}
		t->height = max(height(t->left), height(t->right)) + 1;
  }      
	
	int height(AvlNode<Comparable> *t) const{
		if (t == NULL)
	       return -1;
	
        return t->height;
	}
    int max(int lhs, int rhs) const{
		if (lhs > rhs)
	      return lhs;

        return rhs;            
	}

    void rotateWithLeftChild(AvlNode <Comparable> * & k2) const{
		AvlNode<Comparable> *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
	}
    void rotateWithRightChild(AvlNode <Comparable> * & k1) const{
		AvlNode <Comparable> *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
	}
    void doubleWithLeftChild(AvlNode<Comparable> * & k3) const{
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
	}
    void doubleWithRightChild(AvlNode<Comparable> * & k1) const{
		rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
	}

};

#endif