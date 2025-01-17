// Insertion-sort method for sorting array of integers

#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
using namespace std;

// Insertion-sort process
void InsertionSort(int * A, int N)
{
   int i, j;                           // dummy indices
   int key;                            // current item to be sorted
   // Sort
   for (i = 1; i < N; i++) {           // outer loop sorts the subarray A[0:i-1]
      key = A[i];                      // select current item to be sorted
      // insert item in correct position of already sorted subarray that precedes it
      j = i - 1;                       // begin by checking item immediately preceding current item
      while (j >= 0 && A[j] > key) {   // continue checking until end of subarray or correct position is found
         A[j+1] = A[j];                // move item one position up in the new sorted subarray
         j--;                          // move on to the next item
      };
      A[j+1] = key;
   };
};

// Check if array is sorted
bool CheckSort(int * array, int N)
{
   for (int i = 0; i < N-1; i++) {
      if (array[i] > array[i+1]) return false;  // if any elements out of order, return false
   };
   return true;                                 // if all elements in order, return true
};

// Print array
void PrintArray(int * array, int N, int M)
{
   int n_digits = floor(log10(M) + 1.0) + 1;    // find width for output as number of digits possible plus 1 (for space)
   for (int i = 0; i < N; i++) cout << setw(n_digits) << array[i];
   cout << endl;
};

// Automatically test Sorting function
void AutomatedTest(int * array, int N, int M)
{
   int n_tests = 1000;                          // number of tests to perform
   int pass = 0;                                // number of tests passed
   for (int test = 0; test < n_tests; test++) {
      for (int i = 0; i < N; i++) array[i] = rand() % M;  // Generate random values
      InsertionSort(array, N);         // sort array
      if (CheckSort(array,N)) pass++;  // if array was correctly sorted, add count it
      else PrintArray(array,N,M);      // otherwise, output for inspection
   };
   // Print results of automated testing
   cout << "Automated Testing Results: " << pass
        << " out of " << n_tests
        << " correctly sorted." << endl;
};

int main() {
   // Variable definition
   int N;                     // size of array
   int M;                     // maximum possible value of elements in array
   int *array;                // array to sort

   srand(time(NULL));         // initalize random seed

   // Input basic parameters
   cout << "Number of elements in array: ";           // Ask for size of array
   cin >> N;
   cout << "Maximum possible value of elements: ";    // Ask for maximum possible value
   cin >> M;

   array = new int[N];        // Allocate memory for array

   do {
      for (int i = 0; i < N; i++) array[i] = rand() % M;  // Generate random values
   } while (CheckSort(array,N));    // randomize values until array is not sorted

   PrintArray(array,N,M);     // print array

   InsertionSort(array, N);   // sort array

   PrintArray(array,N,M);     // print array

   // Output status message
   if (CheckSort(array,N)) cerr << "Array sorted!" << endl;
   else cerr << "Array not sorted!" << endl;

   AutomatedTest(array,N,M);  // perform automated testing

   delete[] array;            // De-allocate memory
   return 0;                  // End of the program
}