/***
Purpose: To understand Linked Lists
Author: Göktuð Gençkaya
Date: 15.03.2021
Any know bugs: 
***/

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct node {
	int value;
	node* next;
	node::node()
	{}

	node::node(const int & s, node* link)
		:value(s), next(link)
	{}
	
};

bool innode(node * head, int num){
	bool inside = false;
	node* ptr = head;
	while(ptr != NULL){
		if (ptr->value == num){
			inside = true;
		}
		ptr = ptr->next;
	}
	return inside;
}

/* Begin: code taken and updated from course slides */
void PrintList(node * head){
	if(head == NULL)
		cout << "None";
	node* ptr = head;
	while(ptr != NULL){
		cout << ptr->value << " ";
		ptr = ptr->next;
	}
}
/* End: code taken and updated from course slides */

/* Begin: code taken from Lab examples */
void ClearList(node*head){
	while (head!= NULL){
		node *temp = head;
		head = head->next;
		delete temp;
	}
}
/* End: code taken from Lab examples */



int main() {
	string ordermode;
	cout << "Please enter the order mode (A/D): ";
	cin >>ordermode;
	int i=0;
	while(cin.fail() || !(ordermode == "A" || ordermode == "D")){
		while(ordermode.at(i)==' ') { //Check if there's spaces before the first character input
			i++;
		}
		if (!((ordermode.at(i)== 'A' || ordermode.at(i)== 'D') &&(ordermode.at(i+1)== ' '))) { //make sure first character is D or A but not anything else like DE 
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout << "Please enter the order mode again (A/D): ";
			cin >> ordermode;
		}
	}
	char orderm = ordermode.at(i);
	cin.ignore(numeric_limits<streamsize>::max(),'\n'); 
	cout <<"Please enter the numbers in a line: ";
	string numbers;
	getline(cin,numbers);
	if (numbers ==""){
		cout << "The list is empty at the end of the program and nothing is deleted." << endl;
	}
	else {
		istringstream stream(numbers);
		int num;
		node * head = NULL;
		while(stream >> num){
			cout << endl;
			if (!(innode(head, num))){ //if num is in the linked list, ignore it and go on
				node* del = NULL;
				if (orderm=='A'){
					if(head == NULL || head->value >num){
						if(head != NULL){
							del = head;
						}
						head = new node(num, NULL);
					}
					else if(head->value < num){
						node * ptr = head;
						while(!((ptr->next == NULL) || (ptr->next->value > num))){
							ptr = ptr->next;
						}
						del = ptr->next;
						ptr->next= new node(num,NULL);
					}
				}
				else if(orderm == 'D'){
					if(head == NULL || head->value <num){
						if (head != NULL){	
							del = head;
						}
						head = new node(num, NULL);
					}
					else if(head->value > num){
						node * ptr = head;
						while(!((ptr->next == NULL) || (ptr->next->value < num))){
							ptr = ptr->next;
						}
						del = ptr->next;
						ptr->next= new node(num,NULL);
					}
				}
				//cout statements
				cout << "Next Number: "<< num << endl
					<<"Deleted Nodes: " ;
				PrintList(del);
				ClearList(del);
				cout << endl << "Appended: "<< num << endl
					<< "List Content: " ;
				PrintList(head);
				cout << endl<< endl;
			}
			else {
				cout << "Next Number: "<< num << endl
					<< num << " is already in the list!"<< endl << "List Content: ";
				PrintList(head);
				cout << endl<< endl;
			}
		}
		cout << "All the nodes are deleted at the end of the program:" ;
		PrintList(head);
		cout << endl;
		ClearList(head);
	}
	return 0;
}
