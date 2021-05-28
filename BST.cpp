 //============================================================================
// Name         : lab8.cpp
// Author       : Khalid Mengal
// Version      : 1.0
// Date Created : 04-11-2019
// Date Modified: 01-11-2020 
// Description  : BST Tree implementation in C++
// Copyright © 2020 Khalid Mengal. All rights reserved.
//============================================================================
#include<iostream>
#include<cstdlib>

using namespace std;

class Node
{
	private:
		int key;
		Node* left;
		Node* right;
	public:
		Node(int key);
		~Node();
		int getKey() { return this->key;}
		friend class BST;
};

Node::Node(int key)
{
	this->key = key;
	this->left = nullptr;
	this->right = nullptr;
}
Node::~Node()
{
	cout<<"deleted.."<<this->key<<endl;
}
//=============================================================================
class BST
{
	private:
		Node *root;
	public:
		BST();									//constructor
		~BST();									//destructor
		Node* getRoot();						//returns the root of the Tree
		Node* insert(Node* ptr,int key);		//Insert key into tree/subtree with root ptr
		void printInorder(Node* ptr);			//Traverse (inroder) and print the key of a tree/subtree with root ptr
		int height(Node *ptr);				    //Find the height(MaxDepth) of a tree/subtree with root ptr
		Node* findMin(Node *ptr);				//Find and return the Node with minimum key value from a tree/subtree with root ptr
		Node* findMax(Node *ptr);				//Find and return the Node with Max key value from a tree/subtree with root ptr		
		Node* findKey(Node *ptr,int key);		//Find and returns the node with key
		Node* remove(Node *ptr,int key);		//Remove a node with key from the tree/subtree with root
		void printTree();						//Print 2D Tree
	public:	//helper methods
		void insert_helper(int key);				//Helper method for insert method
		void remove_helper(int key);				//Helper method for remove method
	private:
		void printTreeHelper(int *A, bool *B, Node *ptr, int n); //Helper method for PrintTree()
};

//==========================================================
void listCommands()
{
	cout<<"----------------------------------"<<endl;
	cout<<"display            :Display the BST Tree"<<endl
		<<"insert <key>       :Insert a new node in BST"<<endl
		<<"remove <key>       :Remove the node from BST "<<endl
		<<"height             :Find the hieght of the Tree"<<endl
		<<"min                :Find the node with minimum key in BST"<<endl
		<<"max                :Find the node with maximum key in BST"<<endl
		<<"find <key>         :Find a node with a given key value in BST"<<endl
		<<"inorder            :Print the BST in Inorder"<<endl
		<<"help               :Display the available commands"<<endl
		<<"exit               :Exit the program"<<endl;
}
//==========================================================
void demo( BST &myBST)
{
	myBST.insert_helper(10);
	myBST.insert_helper(5);
	myBST.insert_helper(4);
	myBST.insert_helper(7);
	myBST.insert_helper(13);
	myBST.insert_helper(15);
	myBST.insert_helper(12);
	myBST.insert_helper(14);
	myBST.printTree();
}
//==========================================================
int main(void)
{
	BST myBST;
	listCommands();
	string user_input;
	string command;
	string key;

	while(true)
	{
		cout<<">";
		getline(cin,user_input);

		command = user_input.substr(0,user_input.find(" "));
		key = user_input.substr(user_input.find(" ")+1);
		
		Node* root = myBST.getRoot();	//get the root of the tree
		cout<<"----------------------------------"<<endl;
		if( user_input =="display")	myBST.printTree();
		else if( command =="insert" or command=="i")	{ myBST.insert_helper(stoi(key)); myBST.printTree();} 
		else if( command =="remove" or command=="r")	{ myBST.remove_helper(stoi(key)); myBST.printTree();}
		else if( command =="height")	cout<<"Height = "<<myBST.height(root)<<endl;
		else if( command =="min")	
		{
			Node* min = myBST.findMin(root);
			cout<<"Min. key = "<<((min!=nullptr)? to_string(min->getKey()):" does not exist")<<endl;
		}
		else if( command =="max")	
		{
			Node* max = myBST.findMax(root);
			cout<<"Max. key = "<<((max!=nullptr)? to_string(max->getKey()):" does not exist")<<endl;
		}
		else if( command =="find")	cout<<key<<(myBST.findKey(root,stoi(key))==nullptr ? " not found":" found")<<endl;
		else if( command =="inorder")	{myBST.printInorder(root); cout<<endl;}
		else if( command == "demo") demo(myBST); 
		else if( command == "help") listCommands();
		else if( command == "exit") break;
		else cout<<"Invalid command !!!"<<endl;

	}

	return 0;
}
//=====================================================================

BST::BST()
{
	this->root=nullptr;
}
BST::~BST()
{
	//Keep removing the root of the tree untill it becomes empty
	while(root)
		root=remove(root,root->key);
}
Node* BST::getRoot() 
{
	return this->root;
}					
Node* BST::insert(Node* ptr, int key) {
	if (ptr == NULL) {
		Node* newnode = new Node(key);
		return newnode;
	}
	if (ptr->key < key)
		ptr->right = insert(ptr->right, key);
	else if (ptr->key > key)
		ptr->left = insert(ptr->left, key);
	return ptr;
}	
void BST::printInorder(Node* ptr) {
	if (ptr == NULL) 
		return;
	printInorder(ptr->left);
	cout << ptr->key << " ";
	printInorder(ptr->right);

}
int BST::height(Node* ptr) {
	if (ptr == NULL) 
		return -1;
	return 1 + max(height(ptr->left), height(ptr->right));
}			   
Node* BST::findMin(Node* ptr) {
	if (ptr == NULL) 
		return NULL;
	while (ptr->left!=NULL) {
		ptr = ptr->left;
	}
	return ptr;
}			
Node* BST::findMax(Node* ptr) {
	if (ptr == NULL) 
		return NULL;
	while (ptr->right != NULL) {
		ptr = ptr->right;
	}
	return ptr;
}				
Node* BST::findKey(Node* ptr, int key) {
	if (ptr == NULL) 
	{
		return NULL;
	}
	if (ptr->key == key)
		return ptr;
	else if (ptr->key < key)
		return findKey(ptr->right, key);
	else
		return findKey(ptr->left, key);
}	
Node* BST::remove(Node* ptr, int key) {
	if (key < ptr->key) {
		ptr->left = remove(ptr->left, key);
		return ptr;
	}
	else if (key > ptr->key) {
		ptr->right = remove(ptr->right, key);
		return ptr;
	}
	else {
		if (ptr->left == NULL && ptr->right == NULL) {
			delete ptr;
			return NULL;
		}
		else if (ptr->right == NULL) {
			Node* tmp = ptr->left;
			delete ptr;
			return tmp;
		}
		else if (ptr->left == NULL) {
			Node* tmp = ptr->right;
			delete ptr;
			return tmp;
		}
		else {
			Node* found = findMin(ptr->right);
			int temp = found->key;
			found->key = ptr->key;
			ptr->key = temp;
			ptr->right = remove(ptr->right, found->key);
			return ptr;
		}
	}
}
//Helper method for insert method
void BST::insert_helper(int key)
{	
	if (findKey(root, key))
		cout << "No duplicates allowed" << endl;
	else
		root=insert(root,key);
}
//=================================================
//Helper method for remove 
void BST::remove_helper(int key)
{
	if(findKey(root,key)==nullptr)
		cout<<"Key not found..."<<endl;
	else
		root = remove(root, key);
}
//==================================================================
//  This method prints a Binary Tree in 2D format
//  Created by Saurabh Ray 
//  Copyright © 2020 Saurabh Ray. All rights reserved.

void BST::printTree(){
   char *space = (char *) "  ";
   int d = height(this->getRoot());
   int n = (1<<(d+1))- 1; // n = 2^(d+1)-1

   int *A = new int[n];
   bool *B = new bool[n];
   for(int i=0; i<n; ++i) 
   	  B[i]=false;

   printTreeHelper(A,B,root,n);

   cout<<"\nTree:"<<endl;
   for(int t=(n+1)/2; t>0; t=t/2){
        for(int j=0; j<n; j++){
            if( ((j+1)%t == 0) && B[j]){
                cout<<A[j];
                B[j] = false;
            }
            else{
                cout<<space;
            }
        }
        cout<<endl;
   }
   cout<<endl;
   delete [] A;
   delete [] B;
}

void BST::printTreeHelper(int *A,bool *B, Node *ptr, int n){
    if(ptr!=nullptr){
        int mid = (n-1)/2;
        A[mid] = ptr->key;
        B[mid] = true;
        printTreeHelper(A,B,ptr->left,mid);
        printTreeHelper(A+(mid+1),B+(mid+1), ptr->right, mid);
    }
}