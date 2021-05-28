/*--------------------------------------------------------------------------*/
/* Name: Sagynbek Talgatuly Student Number: st4121							*/
/* Date: January 23. 2021													*/
/* Program: Task3c.cpp														*/
/* Description: This program displays all the prime                         */
/*              numbers which are less or equal to the input number         */
/*--------------------------------------------------------------------------*/

#include <iostream>
using namespace std;

int main() {
    int a;
    bool flag;
    int ctr = 0;
    cout << "Please, enter the number : ";
    cin >> a;
    //the algorithm is from task 3b
    for (int  j = 2; j <= a; j++){
        int k = 2;
        flag = false;
        while (k * k <= j && flag == false) {
            if (j % k == 0) {
                flag = true;
            }
            k++;
        }
        //each time the prime is found, ctr is incremented
        if (flag == false) { cout << j << endl; ctr++; }
    }
    //the ctr is output and displayed
    cout << "The number of primes which are less or equal to " << a << " is " << ctr << endl;
    return 0;
}


