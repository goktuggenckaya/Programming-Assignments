/* Goktug Genckaya
27888
CS300 THE1
STACKS
Stack Class Implementation (Taken from lecture slides)
*/
#include "goktuggenckaya_genckaya_goktug_hw1_dynstackclass.h"
#include <iostream>

using namespace std;

template <class object>
Stack<object>::Stack(){
	topofStack = NULL;
}

template <class object>
bool Stack<object>::IsFull() const {
	return false;
}

template <class object>
bool Stack<object>::IsEmpty() const{
	return topofStack == NULL;
}

template <class object> 
const object & Stack<object>::top() const{
	return topofStack->element;
}

template <class object>
void Stack<object>::Push(const object & x){
	topofStack = new ListNode(x, topofStack);
}

template <class object>
void Stack<object>::Pop(){
	ListNode * oldtop = topofStack;
	topofStack = topofStack->next;
	delete oldtop;
}

template <class object>
object Stack<object>::topAndPop() {
	object topitem = top();
	Pop();
	return topitem;
}

template <class object>
void Stack<object>::MakeEmpty() {
	while (!IsEmpty()){
		Pop();
	}
}

template <class object>
const Stack<object> & Stack<object>::operator= (const Stack<object> & rhs) {
	if (*this != &rhs){
		MakeEmpty();
		if (rhs.IsEmpty()){
			return *this;
		}
		ListNode *rptr= rhs.topofStack;
		ListNode *ptr = new ListNode(rptr->element);
		topofStack = ptr;
		for(rptr = rptr->next; rptr != NULL; rptr = rptr->next){
			ptr->next = new ListNode(rptr->element);
			ptr = ptr->next;
		}
	}
	return *this;
}

template <class object>
Stack<object>::Stack(const Stack<object> & rhs){
	topofStack = NULL;
	*this = rhs;
}

template <class object>
Stack<object>::~Stack(){
	MakeEmpty();
}








