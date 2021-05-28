/*--------------------------------------------------------------------------*/
/* Name: Sagynbek Talgatuly Student Number: st4121							*/
/* Date: January 23. 2021													*/
/* Program: Task1.cpp														*/
/* Description: This program converts the temperature measuring             */
/*				from Celsius to Farenheits.									*/
/*--------------------------------------------------------------------------*/

#include <iostream>

using namespace std;

int main() {

	double tempInC, tempInF;
	cout << "Enter the temperature value in Celsius: ";
	//input the temperature value
	cin >> tempInC;
	//calculating the value in Farenheits
	tempInF =  tempInC * 9.0 / 5.0 + 32;
	//output the result
	cout << "Temperature value in Farenheit is: " << tempInF << endl;
	return 0;
	
}


