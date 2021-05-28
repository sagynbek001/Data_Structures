//============================================================================
// Name         : lab12.cpp
// Author       : Khalid Mengal
// Version      : 1.0
// Date Created : 25-04-2020
// Date Modified: 22-11-2020 
// Copyright    : All rights are reserved
// Description  : HashTable using seperate chaining
//============================================================================

#include<iostream>
#include<fstream>
#include<sstream>
#include<math.h>
#include<list>


using namespace std;
class HashNode
{
	private:
		string key;
		string value;
	public:
		HashNode(string key, string value)
		{
			this->key = key;
			this->value = value;
		}
		friend class HashTable;

};

class HashTable
{
	private:
		list<HashNode> *buckets;		// Array of lists of type Hash Nodes
		int size;					    // Current Size of HashTable
		int capacity;				    // Total Capacity of HashTable
		int collisions;					// Total Number of Collisions
	public:
		HashTable(int capacity);
		unsigned long hashCode(const string key);
		void insert(const string key, const string value);
		string search(const string key);
		void searchAll(const string key);
		void erase(const string key);
		int getSize();
		int getCollisions();
		~HashTable();

};
HashTable::HashTable(int capacity)
{
	buckets = new list<HashNode>[capacity];			//Create an array of size capacity. Each locaiton of Array is a list/chain
	this->capacity = capacity;
	this->size = 0;
	this->collisions = 0;
}

unsigned long HashTable::hashCode(const string key)
{
	//TODO	
	int keysize = key.length();
	unsigned long out = 0;
	for (int i = 0; i < keysize; i++)
		out += key[i] * pow(i, 10);
	return out;
}
//================================================
void HashTable::insert(const string key, const string value)
{
	//TODO
	unsigned long index = (hashCode(key)*31 + 17) % capacity;

	if (search(key) == "Record Not Found...!") {
		if (!buckets[index].empty())
			collisions++;
		buckets[index].push_back(HashNode(key, value));
		size++;
	}
	else {
		for (auto it = buckets[index].begin(); it != buckets[index].end(); it++) {
			if (it->key == key) {
				it->value = value;
				return;
			}
		}
	}
}
//===================================================
string HashTable::search(const string key)
{
	//TODO
	unsigned long index = (hashCode(key) * 31 + 17) % capacity;
	int comparisions = 0;

	for (auto it = buckets[index].begin(); it != buckets[index].end(); it++) {
		comparisions++;
		if (it->key == key)
			return it->value + " (comparisions = " + to_string(comparisions) + ")";
	}
	return "Record Not Found...!";
}
//====================================================
void HashTable::searchAll(const string key)
{

}
//=====================================================
void HashTable::erase(const string key)
{
	//TODO
	unsigned long index = (hashCode(key) * 31 + 17) % capacity;
	for (auto it = buckets[index].begin(); it != buckets[index].end(); it++) {
		if (it->key == key) {
			cout << "Deleted: " << key << ", " << it->value << endl;
			buckets[index].erase(it);
			return;
		}
	}
	cout << "Record Not Found...!" << endl;
}
//=====================================================
int HashTable::getSize()
{
	return this->size;
}
//======================================================
int HashTable::getCollisions()
{
	return this->collisions;
}
//======================================================
HashTable::~HashTable()
{
	for(int i=0; i<capacity; i++)
		buckets[i].clear();
	
	delete[] this->buckets;
}

//======================================================
int main(void)
{
	ifstream fin;
	fin.open("zipcodes.txt");
	if(!fin){
		cout<<"Can not open the file <zipcodes.txt>...!"<<endl;
		exit(-1);
	}

	string line;
	HashTable myHashTable(25847);// Prime number bigger than > 19880*1.333;
	getline(fin,line);  //skip first line
	while(!fin.eof())
	{
		string key, value;
		getline(fin,value,',');
		getline(fin,key);
		cout<<key<<":"<<value<<endl;
		myHashTable.insert(key,value);

	}
	fin.close();
	cout<<"==================================================="<<endl;
	cout<<"Hash Table size = "<<myHashTable.getSize()<<endl;
	cout<<"Total Number of Collisions = "<<myHashTable.getCollisions()<<endl;
	cout<<"Avg. Number of Collisions Per Entry = "<<float(myHashTable.getCollisions())/myHashTable.getSize()<<endl;
	cout<<"==================================================="<<endl;

	string user_input, command, argument1, argument2;

	while(true)
	{
	
		cout<<">";
		getline(cin,user_input);

		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,argument1,',');
		getline(sstr,argument2);

			if(command == "search") cout<<"Zip code for "<<argument1<<" is: "<<myHashTable.search(argument1)<<endl;
		// else if(command == "searchAll") myHashTable.searchAll(argument1);
		else if(command == "insert") {myHashTable.insert(argument1,argument2);}
		else if(command == "erase")	  myHashTable.erase(argument1);
		else if(command == "help")	  cout<<"Commands available \ninsert <key,value>\nsearch <key>\nerase <key>"<<endl;
		else if(command == "exit")	  break;
		else cout<<"Invalid command !!!"<<endl;
	}
	return 0;
}



