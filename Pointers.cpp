#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

void findMinMax(int[],int, int&, int&);	//function declaration

int main(void)
{
	srand(time(NULL));
	//Declare variables
	int size;
	int* arr;
	int min, max;
	//Prompt user for the array size
	cout << "Enter the size of the array: ";
	cin >> size;
	if (size < 1) { cerr << "Invalid size" << endl; return 0; }
	//Create dynamic array
	arr = new int[size];
	//Populate the array with random values
	for (int i = 0; i < size; i++) {
		arr[i] = rand() % 101;
	}
	//Call function finMinMax()
	findMinMax(arr, size, min, max);
	//Print the values of array followed by min and max values
	for (int i = 0; i < size; i++) {
		cout << "Array [" << i << "] = " << arr[i] << endl;
	}
	cout << endl;
	cout << "Min is: " << min << endl;
	cout << "Max is: " << max << endl;
	//Do Necessary cleanup, e.g. delete dynamically allocated memory.
	delete[] arr;
	return EXIT_SUCCESS;
}

//Function Definition
void findMinMax(int array[], int arraySize, int& min, int& max)
{
	//define function body.
	min = array[0];
	max = array[0];
	for (int i = 0; i < arraySize; i++) {
		if (array[i] > max) { max = array[i]; }
		if (array[i] < min) { min = array[i]; }
	}
}