/* Begin: code taken and updated from DynamicStringStack.h */


#ifndef DYNAMICSTACK_H
#define DYNAMICSTACK_H

#include <string>
using namespace std;

struct StackNode
{
	string value;
	StackNode *next;
	StackNode::StackNode(string val, StackNode* next )
		:value(val), next(next)
	{}
	StackNode::StackNode(){
		string value;
		StackNode *next = NULL;
	}
};


class DynamicStack
{
	private:
		StackNode *top;
		StackNode* GetTopPointer(DynamicStack myStack);

	public:
		DynamicStack(void); //constructor
		//~DynamicStack(void); //destructor 
		void push(string);
		void pop(string &);
		bool isEmpty(void);
		DynamicStack(const DynamicStack &); //deep copy constructor
		StackNode * createClone() const;
		
};


#endif

/* End: code taken and updated from DynamicStringStack.h*/