/*--------------------------------------------------------------------------*/
/* Name: Sagynbek Talgatuly Student Number: st4121							*/
/* Date: January 23. 2021													*/
/* Program: Task2.cpp														*/
/* Description: This program calculates the cost of the electricity bill    */
/*--------------------------------------------------------------------------*/

#include <iostream>

using namespace std;

int main() {

	int prev, now;
	cout << "Enter the current meter reading: ";
	//inputting the reading values
	cin >> now;
	cout << "Enter the previous meter reading: ";
	cin >> prev;
	int units = now - prev;
	int bill;
	//calculations
	if (units > 500) { bill = (units - 500) * 100 + 18000; }
	else if (units > 200) { bill = (units - 200) * 50 + 3000; }
	else if (units > 100) { bill = (units - 100) * 20 + 1000; }
	else { bill = 10 * units; }
	//outputting the result
	cout << "The cost of the electricity bill is: " << bill/100.0 << " " << "AED" << endl;
	return 0;

}
