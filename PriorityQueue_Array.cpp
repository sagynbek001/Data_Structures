//============================================================================
// Name         : lab6_1.cpp
// Author       : Sagynbek Talgatuly
// Version      : 1.0
// Date Created : 28/02
// Date Modified: 28/02 
// Copyright    : All rights are reserved
// Description  : Queue implementation using internal Array
//============================================================================

#include<iostream>
#include<iomanip> //for setw() manipulator
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
class QueueFull: public exception
{
public:
	virtual const char* what() const throw()
	{
		return "Queue is Full";
	}
};
//=================================================

template <typename T>
class Queue
{
	private:
		T *array;
		int n;	//number of current elements in the Queue
		int N;	//Array Size (Capacity)
		int f;	//index of front element
		int r;	//index where a new element will be added
	public:
		Queue(int N);
		~Queue();
		void enqueue(T); 
		T dequeue();
		T& front();
		bool isEmpty();
		bool isFull();
		void display();
};

//===========================================
void listCommands();
//===========================================

int main()
{
	Queue<int> myQueue(5);
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
			if(command=="display") 				myQueue.display();
			else if(command=="enqueue")			myQueue.enqueue(stoi(parameter)),myQueue.display();
			else if(command=="dequeue")			cout<<myQueue.dequeue()<<" removed."<<endl,myQueue.display();
			else if(command=="front")			cout<<myQueue.front()<<endl;
			else if(command=="isEmpty")			cout<<boolalpha<<myQueue.isEmpty()<<endl;
			else if(command=="isFull")			cout<<boolalpha<<myQueue.isFull()<<endl;
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
//==========================================
void listCommands()
{
	cout<<"List of available Commands:"<<endl
		<<"display            : Display the Queue"<<endl
		<<"enqueue <element>  : Enqueue an element in the Queue"<<endl
		<<"dequeue            : Dequeue an element from the Queue"<<endl
		<<"front              : Return the (reference of) front element"<<endl
		<<"isEmpty            : Check if the Queue is Empty or not ?"<<endl
		<<"isFull             : Check if the Queue is Full or not ?"<<endl
		<<"help               : Display the list of available commands"<<endl
		<<"exit/quit          : Exit the Program"<<endl;
}
//===========================================
template<typename T> void Queue<T>::display()
{
	cout<<"+";
	for(int i=0; i<N; i++)
		cout<<"---+";
	cout<<endl;
	for(int i=0; i<N; i++)
	{
		string str="|";
		if(i==f)
			str+="F";
		if(i==r)
			str+="R";
		str+=" ";
		cout<<left<<setw(4)<<str;

	}
	cout<<"|";
	cout<<endl<<"+";
	for(int i=0; i<N; i++)
		cout<<"---+";	
		cout<<endl;
	for(int i=0; i<N; i++)
	{
		if(((f<r) and (i>=f and i<r)) or ((f > r) and (i>=f or i<r )) or n==N)
		{cout<<"|"<<setw(3)<<array[i];
		}
		else
			cout<<"|   ";	
	}
	cout<<"|"<<endl<<"+";
	for(int i=0; i<N; i++)
		cout<<"---+";	

	cout<<endl;
}

template<typename T> Queue<T>::Queue(int N) {
	array = new T[N];
	n = 0;	
	this->N = N;	
	f = 0;	
	r = 0;	
};
template<typename T> Queue<T>::~Queue() {
	delete[] array;
};
template<typename T> void Queue<T>::enqueue(T element) {
	if (isFull()) 
		throw QueueFull();
	else {
		array[r] = element;
		r++;
		r %= N;
		n++;
	}
};
template<typename T> T Queue<T>::dequeue() {
	if (isEmpty())
		throw QueueEmpty();
	else {
		T old = front();
		f++;
		f %= N;
		n--;
		return old;
	}
};
template<typename T> T& Queue<T>::front() {
	if (isEmpty())
		throw QueueEmpty();
	else return array[f];
};
template<typename T> bool  Queue<T>::isEmpty() {
	return n == 0;
};
template<typename T> bool Queue<T>::isFull() {
	return n == N;
};