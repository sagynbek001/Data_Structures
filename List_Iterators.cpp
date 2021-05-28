//============================================================================
// Name         : lab4.cpp
// Author       : Khalid Mengal
// Version      : 1.0
// Date Created : 13-03-2019
// Date Modified: 09-02-2021 
// Copyright    : All rights are reserved
// Description  : Doubly LinkedList implementation in C++
//============================================================================
#include<iostream>
#include<string>
#include<iomanip>

using namespace std;


template <typename T>
class Node
{
	private:
		T elem; //data element (type string in this case)
		Node* next; //Link (pointer) to the next Node
		Node* prev; //Link (pointer) to the previous Node
		template <typename T2> friend class DoublyLinkedList;
		
	public:
		Node(): next(NULL), prev(NULL)
		{}
		Node(T elem) : elem(elem),next(NULL), prev(NULL)
		{}
};
//==============================================================
template <typename T> 
class DoublyLinkedList
{
	private:
		Node<T>* head; 	// pointer to the head of List
		Node<T>* tail; 	// pointer to the tail of List
	public:
		class Iterator 
		{
			private:
				Node<T>* ptr;
			public:
				Iterator(Node<T>* node) {
					ptr = node;
				}
				T& operator *() {
					return ptr->elem;
				}
				Iterator& operator ++() {
					ptr = ptr->next;
					return *this;
				}
				Iterator& operator --() {
					ptr = ptr->prev;
					return *this;
				}
				bool operator !=(const Iterator& other) const {
					return ptr != other.ptr;
				}
				bool operator ==(const Iterator& other) const {
					return ptr == other.ptr;
				}
		};
		Iterator begin() 
		{
			return Iterator(head->next);
		}
		Iterator end() 
		{
			return Iterator(tail);
		}
		DoublyLinkedList (); // empty list constructor
		~DoublyLinkedList (); // destructor to clean up all nodes
		bool empty() const; // is list empty?
		const T& front() const; // get the value (element) from front Node<T> of list
		const T& back() const;  // get the value (element) from last Node<T> of the List 
		void addBefore(Node<T> *ptr, const T& elem);	 //add a new node before ptr
		void addFront(const T& elem); // add a new node to the front of list
		void addBack(const T & elem); //add a new node to the back of the list
		void removeFront(); // remove front node from list
		void removeBack();  // remove last node from list
		void display() const;	// display all element of the list
};

//===================================
int main()
{
	DoublyLinkedList<int> myList;

	for(int i=0; i<10; i++)
		myList.addBack(i);

	//uncomment following the code to test your iterator once finished
	
	for(auto it:myList)
		cout<<it<<endl;

	return EXIT_SUCCESS;
}
//====================================
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList ()
{
	this->head = new Node<T>();
	this->tail = new Node<T>();
	this->head->next = tail;
	this->tail->prev = head;
}
//============================================================
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList () // destructor to clean up all nodes
{
	while(!empty())
		removeFront();
}
//============================================================
template <typename T>
bool DoublyLinkedList<T>::empty() const // is list empty?
{
	return this->head->next == tail;
}
//============================================================
template <typename T>
const T& DoublyLinkedList<T>::front() const // get front element
{
	if(!empty())
		return this->head->next->elem;
	else
		throw runtime_error("List is Empty");
}
//============================================================
template <typename T>
const T& DoublyLinkedList<T>::back() const // get front element
{
	if(!empty())
		return this->tail->prev->elem;
	else
		throw runtime_error("List is Empty");
}
//============================================================
template <typename T>
void DoublyLinkedList<T>::addBefore(Node<T> *ptr, const T& elem)
{
	Node<T> *tmp = new Node<T>(elem);
	tmp->next = ptr;
	tmp->prev = ptr->prev;
	ptr->prev->next = tmp;
	ptr->prev=tmp;
}
//============================================================
template <typename T>
void DoublyLinkedList<T>::addFront(const T& elem) // add to front of list
{
	addBefore(this->head->next, elem);
}
//============================================================
template <typename T>
void DoublyLinkedList<T>::addBack(const T& elem) // add to Back of the list
{
	addBefore(this->tail, elem);
}
//============================================================
template <typename T>
void DoublyLinkedList<T>::removeFront() // remove front item from list
{
	if(!empty())
	{
		Node<T> *tmp = this->head->next;
		this->head->next = tmp->next;
		tmp->next->prev = head;
		delete tmp;
	}
}
//============================================================
template <typename T>
void DoublyLinkedList<T>::removeBack() // remove last item from list
{
	if(!empty())
	{
		Node<T> *tmp = this->tail->prev;
		this->tail->prev = tmp->prev;
		tmp->prev->next = tail;
		delete tmp;
	}
}
//============================================================
template <typename T>
void DoublyLinkedList<T>::display() const
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

