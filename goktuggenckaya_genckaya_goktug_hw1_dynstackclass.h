/* Goktug Genckaya
27888
CS300 THE1
STACKS
Stack Class Declaration (Taken from lecture slides)
*/

//#ifndef _GOKTUGGENCKAYA_GENCKAYA_GOKTUG_HW1_DYNSTACKCLASS_H
//#define _GOKTUGGENCKAYA_GENCKAYA_GOKTUG_HW1_DYNSTACKCLASS_H
#ifndef _DYNSTACK_H
#define _DYNSTACK_H
using namespace std;

template <class object>
class Stack
{
 public:
	Stack();
	Stack(const Stack & rhs);
	~Stack();
	bool IsEmpty() const;
	bool IsFull() const;
	void MakeEmpty();
	void Pop();
	void Push(const object & x);
	object topAndPop();
	const object  & top() const;
	const Stack & operator=(const Stack & rhs);
 private:
	 struct ListNode {
		object element;
		ListNode *next;
		ListNode(const object & theelement, ListNode * n = NULL) 
			: element(theelement), next(n) {}
	};
	 ListNode * topofStack;
};

#include "goktuggenckaya_genckaya_goktug_hw1_dynstackclass.cpp"

#endif