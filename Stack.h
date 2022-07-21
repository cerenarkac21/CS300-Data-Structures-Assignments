// Ceren Arkac ,28269, CS 300, HW3
#ifndef _ARR_STACK_H
#define _ARR_STACK_H

#include <iostream>

template <class Object>
class Stack
{
public:
	Stack()
	{
		topOfStack = NULL;
		INF = Object();
	}

	bool isEmpty(void) const
	{
		bool status;

		if (topOfStack == NULL)
			status = true;
		else
			status = false;

		return status;
	}
    
	const Object & top() const
	{
		if (isEmpty()){
			return INF;
		}
		else
		{
			return topOfStack->element;
		}
	}

	void makeEmpty()
	{
		while(!isEmpty()){
			pop();
		}
		
	}
	void pop()
	{
		if (isEmpty())
		{
			cout << "The stack is empty.\n";
		}
		else	// pop value off top of stack
		{ 
			StackNode * oldTop = topOfStack;
			topOfStack = topOfStack->next;
			delete oldTop;
			oldTop = NULL;
		}
	}
	void push(const Object & x)
	{
		topOfStack = new StackNode(x, topOfStack);

	}
	Object topAndPop(){
		Object topItem = top();
		pop();
		return topItem;
	}

    private:
		struct StackNode
		{
			Object element;
			StackNode * next;

			StackNode(const Object & theElement, StackNode * n = NULL): element(theElement), next(n) {}

		};

		StackNode * topOfStack;
		Object INF;
};



#endif
