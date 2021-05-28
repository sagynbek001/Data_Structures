//============================================================================
// Name         : lab6_2.cpp
// Author       : Sagynbek Talgatuly
// Version      : 1.0
// Date Created : 28/02
// Date Modified: 28/02
// Copyright    : All rights are reserved
// Description  : Printer Queue implementation Singly LinkedList
//============================================================================

#include<iostream>
#include<iomanip>
#include<exception>
#include<string>
using namespace std;
//===================================================
class QueueEmpty: public exception
{
	public:
		virtual const char* what() const throw()
		{
			return "Queue is Empty"; 
		}
};
//=================================================
template <typename E>
class Node
{
	private:
		E elem; //data element (Generic type E in this case)
		Node* next; //Link (pointer) to the next Node
		
	public:
		Node(E elem) : elem(elem), next(NULL)
		{}
		template <typename T> friend class MyLinkedList;

};
//============================================
template <typename T>
class MyLinkedList
{
	private:
		Node<T>* head; // pointer to the head of list
		Node<T>* tail; // pointer to the tail of the list
	public:
		MyLinkedList (); // empty list constructor
		~MyLinkedList (); // destructor to clean up all nodes
		bool empty() const; // is list empty?
		const T& front() const; // get front element
		void addBack(const T& elem); // add element to back of list
		void removeFront(); // remove front item list
		void displayAll() const;
};
//==========================================
template <typename T>
class Queue
{
	private:
		MyLinkedList<T> list;
	public:
		void add(T);
		T remove();
		bool isEmpty();
		void display();
};
//===========================================
void listCommands();
//===========================================

int main()
{
	Queue<string> printerQueue;
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
			if(command=="display") 				printerQueue.display();
			else if(command=="add")				printerQueue.add(parameter),printerQueue.display();
			else if(command=="print")			cout<<printerQueue.remove()<<" Printed..!"<<endl;
			else if(command=="isEmpty")			cout<<boolalpha<<printerQueue.isEmpty()<<endl;
			else if(command == "help")			listCommands();
			else if(command == "exit" || command=="quit")			break;
			else 								cout<<"Invalid Commad !!"<<endl;
		}
		catch(exception &e)
		{
			cout<<"Exception: Printer "<<e.what()<<endl;
		}

	}while(command!="exit" and command!="quit");

	return EXIT_SUCCESS;
}
//==========================================
void listCommands()
{
	cout<<"List of available Commands:"<<endl
		<<"display            : Display the Jobs in Printer Queue"<<endl
		<<"add <job_name>     : Add a Job in the Printer Queue"<<endl
		<<"print              : Print a Job from the Printer Queue"<<endl
		<<"isEmpty            : Check if the Printer Queue is Empty or not ?"<<endl
		<<"help               : Display the list of available commands"<<endl
		<<"exit/quit          : Exit the Program"<<endl;
}
//====================================
template <typename T> MyLinkedList<T>::MyLinkedList() {
	tail = NULL;
	head = tail;
}; 
template <typename T> MyLinkedList<T>::~MyLinkedList() {
	while (!empty()) removeFront();
}; 
template <typename T> bool MyLinkedList<T>::empty() const {
	return head == NULL;
};
template <typename T> const T& MyLinkedList<T>::front() const {
	return head->elem;
};
template <typename T> void MyLinkedList<T>::addBack(const T& elem) {
	Node<T>* v = new Node<T>(elem);
	if (empty()) {
		tail = v;
		head = v;
	}
	else {
		tail->next = v;
		tail = v;
	}
};
template <typename T> void MyLinkedList<T>::removeFront() {
	if (!empty()) {
		Node<T>* old = head;
		head = old->next;
		delete old;
	}
}
template <typename T> void MyLinkedList<T>::displayAll() const
{
	Node<T> *curr=head;
	while(curr!=NULL)
	{
		cout<<"+------";
		curr=curr->next;
	}
	cout<<"+"<<endl<<"|";
	curr=head;
	while(curr!=NULL)
	{
		cout<<setw(5)<<curr->elem<<" |";
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


//===========================================
template<typename T> void Queue<T>::add(T element) {
	list.addBack(element);
};
template<typename T> T Queue<T>::remove() {
	if (isEmpty())
		throw QueueEmpty();
	else
	{
		T old = list.front();
		list.removeFront();
		return old;
	}
};
template<typename T> bool Queue<T>::isEmpty() {
	return list.empty();
};
template<typename T> void Queue<T>::display()
{
	list.displayAll();	
}