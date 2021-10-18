// Quick-sort method for sorting array of integers

#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
using namespace std;

// Swap function
void Swap(int * a, int * b) {
   int temp = *a;
   *a = *b;
   *b = temp;
}

// Function to partition subarray, which partially orders elements in the process
int Partition(int * A, int p, int r) {
   int pivot = A[r];             // set pivot to last element of subarray by default
   int i = p;                    // set final pivot index to first element by default
   for(int j = p; j < r; j++) {  // iterate over subarray (except for pivot)
      if(A[j] <= pivot) {        // if element is less than pivot
         Swap(A+i,A+j);          // swap elements
         i++;                    // increment final pivot index
      };
   };
   Swap(A+i,A+r);                // swap pivot to its proper place
   return i;                     // return pivot index
} 

// Quick-sort function
void QuickSort(int * A, int p, int r) {
   if(p < r) {                   // if subarray has > 1 element
      int q = Partition(A,p,r);  // partition subarray
      QuickSort(A,p,q-1);        // sort left half
      QuickSort(A,q+1,r);        // sort right half
   };
}

// Function to check if array is sorted
bool CheckSort(int * array, int N) {
   for(int i = 0; i < N-1; i++) {
      if(array[i] > array[i+1]) return false;   // if any elements out of order, return false
   };
   return true;                                 // if all elements in order, return true
}

// Function to print array
void PrintArray(int * array, int N, int M) {
   int n_digits = floor(log10(M) + 1.0) + 1;    // find width for output as number of digits possible plus 1 (for space)
   for(int i = 0; i < N; i++) cout << setw(n_digits) << array[i];
   cout << endl;
}

// Function for automatically test sorting function
void AutomatedTest(int * array, int N, int M) {
   int n_tests = 1000;                          // number of tests to perform
   int pass = 0;                                // number of tests passed
   for(int test = 0; test < n_tests; test++) {
      for(int i = 0; i < N; i++) array[i] = rand() % M;  // Generate random values
      QuickSort(array, 0, N-1);        // sort array
      if(CheckSort(array,N)) pass++;   // if array was correctly sorted, add count it
      else PrintArray(array,N,M);      // otherwise, output for inspection
   };
   // Print results of automated testing
   cout << "Automated Testing Results: " << pass
        << " out of " << n_tests
        << " correctly sorted." << endl;
}

int main() {
   // Variable definition
   int N;                     // size of array
   int M;                     // maximum possible value of elements in array
   int *array;                // array to sort

   srand (time(NULL));        // initalize random seed

   // Input basic parameters
   cout << "Number of elements in array: ";           // Ask for size of array
   cin >> N;
   cout << "Maximum possible value of elements: ";    // Ask for maximum possible value
   cin >> M;

   array = new int[N];        // Allocate memory for array

   do {
      for(int i = 0; i < N; i++) array[i] = rand() % M;  // Generate random values
   } while(CheckSort(array,N));     // randomize values until array is not sorted

   PrintArray(array,N,M);     // print array

   QuickSort(array,0,N-1);    // sort array

   PrintArray(array,N,M);     // print array

   // Output status message
   if(CheckSort(array,N)) cerr << "Array sorted!" << endl;
   else cerr << "Array not sorted!" << endl;

   AutomatedTest(array,N,M);  // perform automated testing

   delete[] array;            // De-allocate memory
   return 0;                  // End of the program
}