/*--------------------------------------------------------------------------*/
/* Name: Sagynbek Talgatuly Student Number: st4121							*/
/* Date: January 23. 2021													*/
/* Program: Task3a.cpp														*/
/* Description: This program finds the max in the							*/
/*				set of 10 integers and its occurence number.				*/
/*--------------------------------------------------------------------------*/

#include <iostream>

using namespace std;

int main() {

	int a;
	int max;
	int occ = 1;
	cout << "Enter 1st number : ";
	//assigning the 1st number to max
	cin >> max;
	for (int i = 0; i < 9; i++) {
		cout << "Enter " << i+2 << "th number : ";
		cin >> a;
		//if a number is greater than max, then we assign it to max
		if (max < a) { max = a; occ = 1; } 
		//if max is encountered then the occurence number is incremented
		else if (max == a) { occ++; }
	}
	cout << "Max = " << max << endl;
	cout << "Occurence = " << occ << endl;
	return 0;

}



