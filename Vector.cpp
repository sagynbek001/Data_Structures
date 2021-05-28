//============================================================================
// Name         : MyVector.cpp
// Author       : Khalid Mengal
// Version      : 1.0
// Date Created : 16-03-2019
// Date Modified: 02-03-2021 
// Copyright    : All rights are reserved
// Description  : Vector implmentation in C++
//============================================================================
#include<iostream>
#include<cstdlib>
#include<iomanip>
#include <stdexcept>

using namespace std;

template <typename T>
class MyVector
{
	private:
		T *data;						//pointer to int(array) to store elements
		int v_size;						//current size of vector (number of elements in vector)
		int v_capacity;					//capacity of vector
	public:
		MyVector();						//No argument constructor
		MyVector(int cap);				//One Argument Constructor
		~MyVector();					//Destructor
		void push_back(T element);		//Add an element at the end of vector
		void insert(int index, T element);
		T& at(int index); 				//return reference to the element at index
		const T& front();				//Returns reference to the first element in the vector
		const T& back();				//Returns reference to the Last element in the vector
		int size() const;				//Return current size of vector
		int capacity() const;			//Return capacity of vector
		bool empty() const; 			//Rturn true if the vector is empty, False otherwise
		void display();
};
//==============================================
void listCommands()
{
	cout<<"List of available Commands:"<<endl
		<<"display                  : Display the Vector"<<endl
		<<"push_back <element>      : Add an element to the end of the vector"<<endl
		<<"insert <index element>   : Insert an element at location index"<<endl
		<<"at <index>               : Returns a reference to an element at a specified location"<<endl
		<<"front                    : Return the (reference of) front element"<<endl
		<<"back                     : Returns a reference to the last element of the vector"<<endl
		<<"size                     : Returns the number of elements in the vector"<<endl
		<<"capacity                 : Returns the capacity of vector"<<endl
		<<"empty                    : Tests if the vector container is empty"<<endl
		<<"exit/quit                : Exit the Program"<<endl;
}
//=============================================
int main()
{

	
	MyVector<int> myVector;
	listCommands();
	string user_input;
	string command;
	string parameter1;
	string parameter2;

	do
	{
		cout<<">";
		getline(cin,user_input);

		command = user_input.substr(0,user_input.find(" "));
		parameter1 = user_input.substr(user_input.find(" ")+1, user_input.length()-user_input.rfind(" "));
		parameter2 = user_input.substr(user_input.rfind(" ")+1);		
		try
		{
			if(command=="display") 				myVector.display();
			else if(command=="push_back")		myVector.push_back(stoi(parameter1)),myVector.display();
			else if(command=="insert")		    myVector.insert(stoi(parameter1),stoi(parameter2)),myVector.display();
			else if(command=="at")			    cout<<myVector.at(stoi(parameter1))<<endl;
			else if(command=="front")			cout<<myVector.front()<<endl;
			else if(command=="back")			cout<<myVector.back()<<endl;
			else if(command=="size")            cout<<myVector.size()<<endl;
			else if(command=="capacity")        cout<<myVector.capacity()<<endl;
			else if(command=="empty")			cout<<boolalpha<<myVector.empty()<<endl;
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
//================================================
template <typename T> MyVector<T>::MyVector() 
{
	data = new int[0];
	v_size = 0;
	v_capacity = 0;
}				
template <typename T> MyVector<T>::MyVector(int cap) 
{ 
	data = new int[cap];
	v_capacity = cap; 
	v_size = 0;
}				
template <typename T> MyVector<T>::~MyVector() 
{ 
	delete[] data; 
}				
template <typename T> void MyVector<T>::push_back(T element)
{
	//doing almost the same as in the insert fn
	//if it needs to be resized we resize it
	//otherwise we just set the last element of the array
	if (v_size >= v_capacity) {
		int newcapacity = 0;
		if (v_capacity == 0)
			newcapacity = 1;
		else newcapacity = 2 * v_capacity;
		T* newdata = new T[newcapacity];
		for (int j = 0; j < v_size; j++)
			newdata[j] = data[j];
		if (data != NULL) delete[] data;
		data = newdata;
		v_capacity = newcapacity;
	}
	data[v_size] = element;
	v_size++;
}
template <typename T> void MyVector<T>::insert(int index, T element) 
{
	if (index > v_size - 1) throw runtime_error("Index is out of range");
	//increasing the size of the array by copy-pasting
	if (v_size >= v_capacity) {
		int newcapacity = 0;
		if (v_capacity == 0)
			newcapacity = 1;
		else newcapacity = 2 * v_capacity;
		T* newdata = new T[newcapacity];
		for (int j = 0; j < v_size; j++)
			newdata[j] = data[j];
		//clearing the old array
		if (data != NULL) delete[] data;
		data = newdata;
		v_capacity = newcapacity;
	}
	//moving the elements one step to the right
	for (int j = v_size - 1; j >= index; j--) 
		data[j + 1] = data[j];
	data[index] = element;
	v_size++;
}
template <typename T> T& MyVector<T>::at(int index) 
{
	if (!empty())
		if (index >= 0 and index < v_size)
			return data[index];
		else throw runtime_error("Out of range");
	else throw runtime_error("The vector is empty");
}
template <typename T> const T& MyVector<T>::front() 
{
	if (!empty())
		return data[0];
	else throw runtime_error("The vector is empty");
}
template <typename T> const T& MyVector<T>::back() 
{	
	if (!empty())
		return data[v_size - 1];
	else throw runtime_error("The vector is empty");
}
template <typename T> int MyVector<T>::size() const 
{
	return v_size;
}
template <typename T> int MyVector<T>::capacity() const 
{
	return v_capacity;
}
template <typename T> bool MyVector<T>::empty() const 
{
	return v_size == 0;
}
template <typename T>
void MyVector<T>::display()
{
	cout<<"+";
	for(int i=0; i<v_capacity; i++)
		cout<<"---+";	
	cout<<" size = "<<v_size<<endl;
	
	for(int i=0; i<v_capacity; i++)
	{
		if(i<v_size)
			cout<<"|"<<setw(3)<<data[i];
		else
			cout<<"|"<<"   ";		
	}
	cout<<"|"<<endl<<"+";
	for(int i=0; i<v_capacity; i++)
		cout<<"---+";
	cout<<" capacity = "<<v_capacity<<endl;	
}
//=================================================