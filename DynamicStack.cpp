/* Begin: code taken and updated from DynamicStringStack.cpp */


#include <iostream>
#include "DynamicStack.h"
using namespace std;

//Constructor
DynamicStack::DynamicStack()
{
	top=NULL;
}

StackNode* DynamicStack::GetTopPointer(DynamicStack myStack)
{
	return myStack.top;
}

//Push back elements to the stack
void DynamicStack::push(string elmt)
{
	StackNode *newNode;

	newNode = new StackNode;
	newNode->value = elmt;

	if(isEmpty())
	{
		top = newNode;
		newNode->next = NULL;
	}
	else
	{
		newNode->next = top;
		top = newNode;
	}
}
//Pop up elements from the stack
void DynamicStack::pop(string &elmt)
{
	StackNode *temp;

	if(isEmpty())
	{
		cout<<"Stack is empty!\n";
	}

	else 
	{
		elmt = top->value;
		temp = top->next;
		delete top;
		top = temp;
	}
}

//If the stack is empty check function
bool DynamicStack::isEmpty()
{
	bool status;

	if(top==NULL)
		status=true;

	else {
		status=false;
	}

	return status;
}
/*
DynamicStack:: ~DynamicStack() {
	StackNode* pointer = top;
	while (pointer->next != NULL){
		StackNode * temp = pointer->next;
		delete pointer;
		pointer = temp;
	}
}
*/
StackNode * DynamicStack::createClone() const{
	if (top == NULL){
		return NULL;
	}
	StackNode * headClone = new StackNode(top->value, NULL);
	StackNode * ptr = top->next;
	StackNode * ptrClone = headClone;
	while (ptr != NULL){
		ptrClone->next = new StackNode(ptr->value, NULL);
		ptr = ptr->next;
		ptrClone = ptrClone->next;
	}
	return headClone;

}
DynamicStack::DynamicStack(const DynamicStack & copyofit){
	top = copyofit.createClone();
}

/* End: code taken and updated from DynamicStringStack.cpp */