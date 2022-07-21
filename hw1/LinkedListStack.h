// Ceren Arkac ,28269, CS 300, HW1
#ifndef _LINKEDLISTSTACK_H
#define _LINKEDLISTSTACK_H

template <class Object>
class Stack
{
public:
	Stack()
	{
		topOfStack = NULL;
	}

	Stack(const Stack & rhs)
	{
		topOfStack = NULL;
		*this = rhs; // deep copy 
	}
	~Stack()
	{
		makeEmpty();
	}

	bool isEmpty( ) const
	{
		return topOfStack == NULL;
	}

	bool isFull() const
	{
		return false;
	}

	void makeEmpty()
	{
		while (!isEmpty())
		{
			pop();
		}
	}


	void pop()
	{
		if (isEmpty())
			//throw Underflow();
			cout << "Stack is empty!" << endl;
		ListNode *oldTop = topOfStack;
		topOfStack = topOfStack->next;
		delete oldTop;
	}
	void push(const Object & x)
    {
		topOfStack = new ListNode(x, topOfStack);
    }

	Object topAndPop()
	{
		Object topItem = top( );
		pop();
		return topItem;
	}
	const Object & top() const
	{
		if (isEmpty())
			//throw Underflow();
			cout << "Stack is empty!" << endl;
		//return topOfStack->element;
		return topOfStack->element;
	}

	const Stack & operator=(const Stack & rhs)
	{
		if (this != &rhs)
		{
			makeEmpty();
			if  (rhs.isEmpty())
				return *this;

			ListNode *rptr = rhs.topOfStack;
			ListNode *ptr  = new ListNode(rptr->element);
			topOfStack = ptr;

			for (rptr = rptr->next; rptr != NULL; rptr = rptr->next)
				ptr = ptr->next = new ListNode(rptr->element);
		}
		return *this;
	}
private:
	struct ListNode
	{
		Object element;
		//int x_cooor, y_cooor;
		ListNode * next;
		ListNode(const Object & theElement, ListNode * n = NULL)
			: element(theElement), next(n) {}
	}; 

	ListNode *topOfStack;  // list itself is the stack
};
#endif