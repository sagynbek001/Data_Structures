//============================================================================
// Name         : lab3.cpp
// Author       : Sagynbek Talgatuly
// Version      : 1.0
// Date Created : 08/02/2021
// Date Modified: 08/02/2021
// Copyright    : All rights are reserved
// Description  : Singly Linked-List implementaiton in C++
//============================================================================
#include<iostream>
#include<string>
#include<fstream>
#include<exception>
using namespace std;
//====================================
class Node
{
	private:
		int elem; //data element 
		Node* next; //Link (pointer) to the next Node
		
	public:
		Node(int elem) : elem(elem), next(NULL)
		{}
		friend class MyLinkedList ;

};
//=====================================
class MyLinkedList
{
	private:
		Node* head; // pointer to the head of list
	public:
		MyLinkedList (); // empty list constructor
		~MyLinkedList (); // destructor to clean up all nodes
		bool empty() const; // is list empty?
		const int& front() const; // get the element/data from the front Node
		void addFront(const int& elem); // add a new Node at the front of the list
		void removeFront(); // remove front Node from the list
		void display() const;
		void loadData(string); //read a file and load it into the linked list
		void dumpData(string) const; //write the linked list to a file
		//Optional Task
		void sort();  // sort the elements of the list
};
//=====================================
void listCommands()
{
	cout<<"List of available Commands:"<<endl
		<<"display            : Display the Linked List"<<endl
		<<"addFront <element> : Add <element> to the front of the Linked List"<<endl
		<<"removeFront        : Remove the front node of the Linked List"<<endl
		<<"load <file_name>   : Load the data from <file> and add it into the Linked List"<<endl
		<<"dump <file_name>   : Dump the contents of the Linked list to <file>"<<endl
		<<"sort               : Sort the Linked List using Bubble Sort Algorithm"<<endl
		<<"help               : Display the list of available commands"<<endl
		<<"exit               : Exit the Program"<<endl;
}
//=======================================
// main function
int main()
{

	MyLinkedList myList;

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
		
		if(command=="display") 				myList.display();
		else if(command=="addFront" or command=="add")				myList.addFront(stoi(parameter)),myList.display();
		else if(command=="removeFront" or command=="remove")		myList.removeFront(),myList.display();
		else if(command=="load")			myList.loadData(parameter),myList.display();
		else if(command == "dump")			myList.dumpData(parameter);
		else if(command == "sort")			myList.sort(),myList.display();
		else if(command == "help")			listCommands();
		else if(command == "exit")			break;
		else 								cout<<"Invalid Commad !!"<<endl;
	}while(command!="exit");

	return EXIT_SUCCESS;
}
//====================================
// constructor
MyLinkedList::MyLinkedList ()
{
	this->head = NULL;
}
//====================================
// destructor to clean up all nodes
MyLinkedList::~MyLinkedList () 
{
	//todo
	while (!empty()) { removeFront(); }
}
//====================================
// Check if the list is empty or not
bool MyLinkedList::empty() const 
{
	//todo 
	return head == NULL;
}
//====================================
// return the value/elemnt at the front of the lsit
const int& MyLinkedList::front() const
{
	//todo
	return head->elem;
}
//====================================
// add a node at the front of list
void MyLinkedList::addFront(const int& elem)
{
	//todd
	Node* v = new Node(elem);
	v->next = head;
	head = v;
}
//====================================
// remove the first node from the list
void MyLinkedList::removeFront()
{
	//todo
	if (!empty()) {
		Node* old = head;
		head = old->next;
		delete old;
	}
}
//====================================
// display all nodes of the linked list
void MyLinkedList::display() const
{
	//todo
	cout << "Head -> ";
	Node* current = head;
	while (current != NULL) {
		cout << current->elem << " -> ";
		current = current->next;
	}
	cout << "NULL" << endl;
}
//====================================

//Load data from a file and add it to the Linked List
void MyLinkedList::loadData(string path)
{
	//todo
	ifstream fin(path);
	if (fin.is_open())
	{
		int in;
		while (!fin.eof()) {
			fin >> in;
			addFront(in);
		}
	}
	else
	{
		cerr << "Invalid Path" << endl;
	}
	fin.close();
}
//=============================================
//Dump/write the contents of the list to a file
void MyLinkedList::dumpData(string path) const
{
	//todo
	ofstream fout(path);
	if (fout.is_open())
	{
		int out;
		Node* current = head;
		while (current != NULL) {
			fout << current->elem << endl;
			current = current->next;
		}
	}
	else
	{
		cerr << "Invalid Path" << endl;
	}
	fout.close();
}
//==================================================
// sort the elments of the list using: Hint use bubble_sort
void MyLinkedList::sort()
{
	//todo
	int counter = 0;
	Node* pointer = head;
	while (pointer != NULL) {
		counter++;
		pointer = pointer->next;
	}
	int i, j;
	for (i = 0; i < counter - 1; i++) {
		pointer = head;
		for (j = 0; j < counter - i - 1; j++) {
			if (pointer->elem > pointer->next->elem) {
				int temp = pointer->next->elem;
				pointer->next->elem = pointer->elem;
				pointer->elem = temp;
			}
			pointer = pointer->next;
		}
	}
}
//==============================================
