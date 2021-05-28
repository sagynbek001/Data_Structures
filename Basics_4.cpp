/*--------------------------------------------------------------------------*/
/* Name: Sagynbek Talgatuly Student Number: st4121							*/
/* Date: January 23. 2021													*/
/* Program: Task3b.cpp														*/
/* Description: This program verifies if the number is prime        		*/
/*--------------------------------------------------------------------------*/

#include <iostream>
using namespace std;

int main() {

    int a;
    //the flag variable is used to exit the loop
    bool flag = false;
    cout << "Please, enter the number : ";
    cin >> a;
    //if the number is less or equal to 1, then it is not prime
    if (a <= 1) {
        cout << "The number is not prime" << endl;
    }
    else {
        int i = 2;
        while (i * i <= a && flag == false) {
            if (a % i == 0) {
                //if the number is divisible by any other number 
                //that is less or equal to its square root
                cout << "The number is not prime" << endl;
                flag = true;
            }
            i++;
        }
        if (flag == false) { cout << "The number is prime" << endl; }
    }
    return 0;

}



