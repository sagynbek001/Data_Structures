//============================================================================
// Name         : lab14.cpp
// Author       : Khalid Mengal
// Version      : 1.0
// Date Created : 08-05-2020
// Date Modified: 08-05-2020 
// Copyright    : All rights are reserved
// Description  : Sorting Algorithms (Selection Sort, Bubble Sort, Insertion Sort, Merge Sort, Quick Sort, Heap Sort)
//============================================================================

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
#define SIZE 10000
#define MAX 500000
template <typename T> void selection_sort(T array[], int n);
template <typename T> void bubble_sort(T array[], int n);
template <typename T> void insertion_sort(T array[], int n);
template <typename T> void merge_sort(T array[], int left, int right);
template <typename T> void merge(T array[], int left, int right, int mid);
template <typename T> void quick_sort(T array[], int left, int right);
template <typename T> int partition(T array[], int left, int right);
template <typename T> void print(T array[], int size);

int main()
{

	int array[SIZE];
	srand(time(NULL));
	for(int i=0; i<SIZE;i++)
		array[i] = rand()%MAX;
	
	int start = clock();
	selection_sort(array,SIZE);
	//print(array, SIZE);
	int stop = clock ();
	cout<<"Selection Sort took: "<<float(stop - start )/  CLOCKS_PER_SEC*1000<<" milliseconds"<<endl;

	random_shuffle(array,array+SIZE);
	start = clock();
	bubble_sort(array,SIZE);
	//print(array, SIZE);
	stop = clock ();
	cout<<"Bubble Sort took: "<<float(stop - start )/  CLOCKS_PER_SEC*1000<<" milliseconds"<<endl;

	random_shuffle(array,array+SIZE);
	start = clock();
	insertion_sort(array,SIZE);
	//print(array, SIZE);
	stop = clock ();
	cout<<"Insertion Sort took: "<<float(stop - start )/  CLOCKS_PER_SEC*1000<<" milliseconds"<<endl;
	
	random_shuffle(array,array+SIZE);
	start = clock();
	merge_sort(array,0,SIZE-1);
	//print(array, SIZE);
	stop = clock ();
	cout<<"Merge Sort took: "<<float(stop - start )/  CLOCKS_PER_SEC*1000<<" milliseconds"<<endl;

	random_shuffle(array,array+SIZE);
	start = clock();
	quick_sort(array,0,SIZE-1);
	//print(array, SIZE);
	stop = clock ();
	cout<<"Quick Sort took: "<<float(stop - start )/  CLOCKS_PER_SEC*1000<<" milliseconds"<<endl;


	return EXIT_SUCCESS;
}
//========================================================
template <typename T> void print(T array[], int size)
{
	for(int i=0; i<size; i++)
		cout<<array[i]<<" ";
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

template <typename T> void selection_sort(T array[], int n) {
	int smallest;
	for (int i = 0; i < n - 1; i++) {
		smallest = i;
		for (int j = i + 1; j < n; j++)
			if (array[j] < array[smallest])
				smallest = j;
		if (smallest != i)
			swap(&array[i], &array[smallest]);
	}
}

template <typename T> void bubble_sort(T array[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			if (array[j] > array[j + 1]) {
				swap(&array[j], &array[j + 1]);
			}
		}
	}
}

template <typename T> void insertion_sort(T array[], int n) {
	int j, tmp;
	for (int i = 1; i < n; i++) {
		tmp = array[i];
		j = i - 1;
		while ((tmp < array[j]) && (j >= 0)){
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = tmp;
	}
}

template <typename T> void merge_sort(T array[], int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		merge_sort(array, left, mid);
		merge_sort(array, mid + 1, right);
		merge(array, left, right, mid);
	}
}

template <typename T> void merge(T array[], int left, int right, int mid) {
	int sizeleft = mid - left + 1;
	int sizeright = right - mid;
	int L[sizeleft], R[sizeright];

	for (int i = 0; i < sizeleft; i++)
		L[i] = array[left + i];
	for (int i = 0; i < sizeright; i++)
		R[i] = array[mid + i + 1];

	int i = 0, j = 0, current = left;
	while (i < sizeleft && j < sizeright)
		array[current++] = L[i] <= R[j] ? L[i++] : R[j++];
	while (i < sizeleft)
		array[current++] = L[i++];
	while (j < sizeright)
		array[current++] = R[j++];
}

template <typename T> void quick_sort(T array[], int left, int right) {
	if (left < right) {
		int pivot = partition(array, left, right);
		quick_sort(array, left, pivot - 1);
		quick_sort(array, pivot + 1, right);
	}
}

template <typename T> int partition(T array[], int left, int right) {
	int pivot = array[right];
	int current_ind = left - 1;
	for (int i = left; i < right; i++) {
		if (array[i] < pivot) {
			current_ind++;
			swap(&array[current_ind], &array[i]);
		}
	}
	swap(&array[current_ind + 1], &array[right]);
	return current_ind + 1;
}

