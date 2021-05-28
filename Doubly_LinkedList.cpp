//============================================================================
// Name         : lab4.cpp
// Author       : Sagynbek Talgatuly
// Version      : 1.0
// Date Created : 12/02/2021
// Date Modified: 15/02/2021
// Copyright    : All rights are reserved
// Description  : Doubly LinkedList implementation in C++
//============================================================================
#include<iostream>
#include<string>
#include<iomanip>
#include<exception>
using namespace std;
typedef string Elem;

class Node
{
	private:
		Elem elem; //data element (type string in this case)
		Node* next; //Link (pointer) to the next Node
		Node* prev; //Link (pointer) to the previous Node
		friend class DoublyLinkedList;
		
	public:
		Node(): next(NULL), prev(NULL)
		{}
		Node(Elem elem) : elem(elem), next(NULL), prev(NULL)
		{}
};
//==============================================================
class DoublyLinkedList
{
	private:
		Node* head; 	// pointer to the head of List
		Node* tail; 	// pointer to the tail of List
	public:
		DoublyLinkedList (); // empty list constructor
		~DoublyLinkedList (); // destructor to clean up all nodes
		bool empty() const; // is list empty?
		const Elem& front() const; // get the value (element) from front Node of list
		const Elem& back() const;  // get the value (element) from last Node of the List 
		void addBefore(Node *ptr, const Elem& elem);	 //add a new node before ptr
		void addFront(const Elem& elem); // add a new node to the front of list
		void addBack(const Elem & elem); //add a new node to the back of the list
		void removeFront(); // remove front node from list
		void removeBack();  // remove last node from list
		void reverseList();	// reverse the list
		bool isPalindrome(); //check if the List is Palindrome or not
		void display() const;	// display all element of the list
};
//===================================
void listCommands()
{
	cout<<"List of available Commands:"<<endl
		<<"display            : Display the Doubly Linkled List"<<endl
		<<"front              : Display the first element of the List"<<endl
		<<"back               : Display the last element of the List"<<endl
		<<"addFront <elem>    : Add a new Node at the begining of the List"<<endl
		<<"addBack  <elem>    : Add a new Node at the end of the List"<<endl
		<<"removeFront        : Remove the first Node of the Linked List"<<endl
		<<"removeBack         : Remove the last  Node of the Linked List"<<endl	
		<<"empty              : Check if the List is empty?"<<endl
		<<"reverse            : Reverse the Linked List"<<endl
		<<"isPalindrome       : Check if the List is Palindrome or not?"<<endl
		<<"help               : Display the list of available commands"<<endl
		<<"exit               : Exit the Program"<<endl;
}
//===================================
int main()
{
	DoublyLinkedList myList;
	listCommands();
	string user_input;
	string command;
	string parameter;

	do
	{
		cout<<">";
		getline(cin,user_input);

		command = user_input.substr(0,user_input.find(" "));
		parameter = user_input.substr(user_input.find(" ")+1);
		
		try
		{
			if(command=="display") 				myList.display();
			else if(command=="front")			cout<<"Front = "<<myList.front()<<endl;
			else if(command=="back")			cout<<"Back = "<<myList.back()<<endl;
			else if(command=="addFront")		myList.addFront(parameter),myList.display();
			else if(command=="addBack")		 	myList.addBack(parameter),myList.display();
			else if(command=="removeFront")		myList.removeFront(),myList.display();
			else if(command=="removeBack")		myList.removeBack(),myList.display();
			else if(command=="empty")			cout<<"List is "<<(myList.empty()? "Empty":"Not Empty")<<endl;
			else if(command=="reverse")			myList.reverseList(),myList.display();
			else if(command=="isPalindrome")	cout<<"List is "<<(myList.isPalindrome()? "Palindrome":"Not Palindrome")<<endl;
			else if(command == "help")			listCommands();
			else if(command == "exit")			break;
			else 								cout<<"Invalid Commad !!"<<endl;
		}
		catch(exception &e)
		{
			cout<<"Exception: "<<e.what()<<endl;
		}

	}while(command!="exit" and command!="quit");

	return EXIT_SUCCESS;
}
//============================================================
DoublyLinkedList::DoublyLinkedList ()
{
	//todo
	head = new Node;
	tail = new Node;
	head->next = tail;
	tail->prev = head;
}
//============================================================
DoublyLinkedList::~DoublyLinkedList () // destructor to clean up all nodes
{
	//todo
	while (!empty()) removeFront();
	delete head;
	delete tail;
}
//============================================================
bool DoublyLinkedList::empty() const // is list empty?
{
	//todo
	return
		head->next == tail &&
		tail->prev == head;
}
//============================================================
const Elem& DoublyLinkedList::front() const // get front element
{
	//todo
	if (!empty()) {
		return head->next->elem;
	}
	else { throw logic_error("The list is empty"); }
}
//============================================================
const Elem& DoublyLinkedList::back() const // get front element
{
	//todo
	if (!empty()) {
		return tail->prev->elem;
	}
	else { throw logic_error("The list is empty"); }
}
//============================================================
void DoublyLinkedList::addBefore(Node *ptr, const Elem& elem)
{
	//todo
	Node* u = new Node;
	u->elem = elem;
	u->next = ptr;
	u->prev = ptr->prev;
	ptr->prev->next = u;
	ptr->prev = u;
}
//============================================================
void DoublyLinkedList::addFront(const Elem& elem) // add to front of list
{
	//todo
	addBefore(head->next, elem);
}
//============================================================
void DoublyLinkedList::addBack(const Elem& elem) // add to Back of the list
{
	//todo
	addBefore(tail, elem);
}
//============================================================
void DoublyLinkedList::removeFront() // remove front item from list
{
	//todo
	if (!empty()) {
		Node* old = head->next;
		head->next = old->next;
		old->next->prev = head;
		delete old;
	}
	else { throw logic_error("No elements to remove"); }
}
//============================================================
void DoublyLinkedList::removeBack() // remove last item from list
{
	//todo
	if (!empty()) {
		Node* old = tail->prev;
		tail->prev = old->prev;
		old->prev->next = tail;
		delete old;
	}
	else { throw logic_error("No elements to remove"); }
}
//============================================================
void DoublyLinkedList::display() const
{
	Node *curr=head;
	while(curr!=NULL)
	{
		cout<<"+------";
		curr=curr->next;
	}
	cout<<"+"<<endl<<"|";
	curr=head;
	while(curr!=NULL)
	{
		if (curr == head)		cout<<" Head |";
		else if(curr == tail)	cout<<" Tail |";
		else 					cout<<setw(5)<<curr->elem<<" |";
	
		curr=curr->next;
	}
	curr=head;
	cout<<endl;
	while(curr!=NULL)
	{
		cout<<"+------";
		curr=curr->next;
	}
	cout<<"+"<<endl;
}
//============================================================
void DoublyLinkedList::reverseList()
{
 	//todo
	if (!empty() && head->next->next!=tail) {
		//swaping the pointers of the first element
		head->next->prev = head->next->next;
		head->next->next = tail;
		Node* pointer = head->next->prev;
		//swaping the pointers of the elements other than fisrt and last
		while (pointer != tail->prev) {
			Node* temp = pointer->prev;
			pointer->prev = pointer->next;
			pointer->next = temp;
			pointer = pointer->prev;
		}
		//swaping the pointers of the last element
		tail->prev->next = tail->prev->prev;
		tail->prev->prev = head;
		Node* temp = head->next;
		head->next = tail->prev;
		tail->prev = temp;
	}
}
//============================================================
bool DoublyLinkedList::isPalindrome()
{
	//todo
	if (!empty()) {
		Node* left = head;
		Node* right = tail;
		while (left != right && left->prev != right) {
			left = left->next;
			right = right->prev;
			if (left->elem != right->elem) return false;
		}
	}
	return true;
}
