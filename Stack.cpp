//============================================================================
// Name         : lab5.cpp
// Author       : Sagynbek Talgatuly
// Version      : 1.0
// Date Created : 23/02/2021
// Date Modified: 23/02/2021
// Copyright    : All rights are reserved
// Description  : Convert Infix expression to PostFix and then evaluate it
//============================================================================
#include<iostream>
#include<string>
#include<math.h>
#include<exception>
#include<stack>
#include<ctype.h>

using namespace std;

template <typename T>
class LinkedList;

template <typename T>
class Node {
private:
	T elem;
	Node<T>* next;
	friend class LinkedList<T>;
};

template <typename T>
class LinkedList {
private:
	Node<T>* head;
public:
	LinkedList()		{ head = NULL; };
	~LinkedList()		{ while (!empty()) removeFront(); };
	void removeFront()	
	{
		Node<T>* old = head;
		head = old->next;
		delete old;
	}
	void addFront(const T& e) {
		Node<T>* v = new Node<T>;
		v->elem = e;
		v->next = head;
		head = v;
	}
	bool empty() const	{ return head == NULL; }
	const T& front()	{ return head->elem; }
};

template <typename T>
class CStack {
public:
	CStack();
	~CStack() { while (!S->empty()) S->removeFront(); }
	int size() const;
	bool empty() const;
	const T& top() const;
	void push(const T& e);
	void pop();
private:
	LinkedList<T>* S;
	int n;
};
template <typename T> CStack<T>::CStack(){
	S = new LinkedList<T>;
	n = 0;
}
template <typename T> int CStack<T>::size() const 
{
	return n;
}
template <typename T> bool CStack<T>::empty() const {
	return n == 0;
}
template <typename T> const T& CStack<T>::top() const {
	if (empty()) throw runtime_error("a");
	else {
		return S->front();
	}
}
template <typename T> void CStack<T>::push(const T& e)
{
	++n;
	S->addFront(e);
}
template <typename T> void CStack<T>::pop()
{
	if (empty()) throw runtime_error("The stack is empty");
	else {
		--n;
		S->removeFront();
	}
}

bool isOperator(char); //Helper method which checks if the input char is an operator
int convertOpToInt (char); //Helper mehtod which converts operators into int so their precdence can be compared
bool isleq(char, char); //Helper method which compare two operators  and return True if first operator has less or equal predence than the right operator
string infix2postfix(string);   //Helper Method which converts an infix notaiton into a postfix notation (lab4)
float evaluate(string postfix);		//Method which will evaluate a PostfixExpression and return the result

//=============Main funciton ==============
int main()
{

	while(true)
	{
		string infix;  						//Infix expression
		cout<<"Enter an Infix Expression: ";
		cin>>infix;
	
		if(infix=="exit") 
			break;

		string postfix = infix2postfix(infix);	//Postfix Expression
		cout<<"The postfix form is: "<<postfix<<endl;
		float ans=evaluate(postfix);			//evaluate the postfix Expresion
		cout<<infix<<"="<<ans<<endl;		//print the final answer
	}

	return EXIT_SUCCESS;
}
//=====================================================================
bool isOperator(char ch)
{
	if( ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='^')
		return true;
	else
		return false;

}
//Helper mehtod which converts operators into int so their precdence can be compared
int convertOpToInt (char ch)
{
    if (ch=='+' || ch=='-') return 1;
    if (ch=='*' || ch=='/') return 2;
    if (ch=='^') return 3;
    return 0;
}
//Helper method which compare two operators and return True if first operator
//has less or equal predence than the right operator
bool isleq(char opA, char opB)
{
	return (convertOpToInt(opA)<=convertOpToInt(opB));
}

// Method which converts an Infix Notaiton to a Postfix notation
string infix2postfix(string infix)
{
	string postfix = "";
	//0.    Create a stack of type char to store operators/parenthesis
	CStack <char> MyStack;
	//1.	Push “(“onto Stack, and add “)” to the end of INFIX.
	MyStack.push('(');
	infix += ")";
	//2.	Scan INFIX from left to right and repeat Step 3 to 6 for each element of X until the Stack is empty.	
	//3.	If an operand is found, add it to POSTFIX.
	//4.	If a left parenthesis is found, push it onto Stack.
	//5.	If an operator is found, then: 
			//a. Repeatedly pop from Stack and add to POSTFIX each operator (on the top of Stack) which has the same precedence as or higher precedence than operator.
			//b. Push the operator onto Stack.
	//.6.	If a ")" is found, then: 
			//a.	Repeatedly pop from Stack and add to POSTFIX each operator (on the top of Stack) until a "(" found.
			//b.	Remove(pop) the "(" from the stack
	int size = infix.length();
	while (!MyStack.empty()){
		for (int i = 0; i < size; i++) {
			if (infix[i] == '(') { MyStack.push('('); }
			else if (infix[i] == ')') {
				while (MyStack.top() != '(') {
					if (isOperator(MyStack.top())) {
						postfix += MyStack.top();
						MyStack.pop();
					}
				}
				MyStack.pop();
			}
			else if (isOperator(infix[i])) {
				if (isOperator(MyStack.top())) {
					while (isleq(infix[i], MyStack.top())) {
						postfix += MyStack.top();
						MyStack.pop();
					}
				}
				MyStack.push(infix[i]);
			}
			else {
				postfix += infix[i];
			}
		}
	}

	return postfix;
}
// //Method which will evaluate a PostfixExpression and return the result
float evaluate(string postfix)		
{	
	//1. Create a stack of type float to store the operands
	CStack <float> MyStack;
	//2. Scan the postfix expression from left to right for every element
		//	 a. if an operand is found push it to the stack
		//   b. if an operator is found pop 2 elements from the stack, apply the operator on it and push the result back to the stack
	//3. return the value from the top of the stack (i.e. the final answer)
	int size = postfix.length();
	for (int i = 0; i < size; i++) {
		if (isOperator(postfix[i])) {
			float a = MyStack.top();
			MyStack.pop();
			float b = MyStack.top();
			MyStack.pop();
			float t;
			if (postfix[i] == '+') { t = b + a; }
			else if (postfix[i] == '-') { t = b - a; }
			else if (postfix[i] == '*') { t = b * a; }
			else if (postfix[i] == '/') { t = b / a; }
			else if (postfix[i] == '^') { t = pow(b, a); }
			MyStack.push(t);
		}
		else { MyStack.push(float((postfix[i])-48)); }
	}	
	return MyStack.top();
}