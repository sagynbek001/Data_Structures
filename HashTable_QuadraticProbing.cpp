//============================================================================
// Name         : lab11.cpp
// Author       : 
// Version      : 1.0
// Date Created : 21-04-2020
// Date Modified: 14-11-2020 
// Description  : HashTable Implementation in C++
// Copyright © 2020 Khalid Mengal. All rights reserved.

#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;
int probes = 0; // record number of probes, increase it every time a collision occurs

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
	HashNode** nodeArray;		// Array of Pointers to Hash Nodes
	int size;					//Current Size of HashTable
	int capacity;				// Total Capacity of HashTable
public:
	HashTable(int capacity)
	{
		nodeArray = new HashNode * [capacity];
		this->capacity = capacity;
		this->size = 0;
	}
	unsigned long hashCode(const string key)//Create Hashcode for key
	{
		//todo
		int keysize = key.length();
		unsigned long out = 0;
		for (int i = 0; i < keysize; i++)
			out += key[i] * pow(i, 10);
		return out;
	}

	void insert(const string key, const string value)// Insert the key and value in Hash Map using Open Addressing Linear Probing
	{
		//todo
		if (size == capacity)
			throw runtime_error("The HashTable is Full");
		unsigned long index = hashCode(key) % capacity;
		unsigned long init = index;

		int i = 0;
		while (nodeArray[index] != NULL)
		{
			probes++;
			i++;
			index = init + i * i;
			index %= capacity;
		}

		nodeArray[index] = new HashNode(key, value);
		size++;
	}
	string search(const string key)// Search for a key in HashTable and return its value
	{
		//todo
		unsigned long index = hashCode(key) % capacity;
		unsigned long init = index;

		int i = 0;

		while (nodeArray[index] != NULL)
		{
			if (nodeArray[index]->key == key)
				return nodeArray[index]->value;
			i++;
			index = init + i * i;
			index %= capacity;
		}

		return "Record Not Found...!";
	}

	int getSize()
	{
		return this->size;
	}

	~HashTable()
	{
		for (int i = 0; i < capacity; i++)
			delete nodeArray[i];
		delete[] this->nodeArray;
	}
};

void foo(string path, int cap) {
	ifstream fin;
	fin.open(path);
	if (!fin) {
		cout << "Can not open the file...!";
		exit(-1);
	}
	string line;
	HashTable myHashTable(cap);
	getline(fin, line);
	int i = 0;
	while (!fin.eof())
	{
		string key, value;
		getline(fin, value, ',');
		getline(fin, key);
		myHashTable.insert(key, value);
	}
	cout << "	Hash Table size = " << myHashTable.getSize() << endl;
	cout << "	Avg. Number of probes = " << float(probes) / myHashTable.getSize() << endl;
	probes = 0;
}

int main(void)
{
	cout << "Quadratic Probing:" << endl;
	foo("onemillion.txt", 1500007);
	foo("tenmillion.txt", 15485867);

	return 0;
}

