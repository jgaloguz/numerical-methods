// Merge-sort method for sorting array of integers

#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>

using namespace std;

// Merge sorted halves
void Merge(int * A, int left, int mid, int right, int M)
{
   int i, j, k;                        // dummy indices
   int N1 = mid-left+1;                // size of left half of array
   int N2 = right-mid;                 // size of right half of array

   int *A1 = new int[N1+1];            // initialize unmerged left half
   int *A2 = new int[N2+1];            // initialize unmerged right half

   // Load arrays
   for (i = 0; i < N1; i++) A1[i] = A[left+i];  // left half
   A1[N1] = M;                                  // left sentinel
   for (i = 0; i < N2; i++) A2[i] = A[mid+1+i]; // right half
   A2[N2] = M;                                  // right sentinel

   // Merge
   i = j = 0;                             // set half counters to zero
   for (k = left; k <= right; k++) {      // merge all elements from left to right
      if (A1[i] < A2[j]) A[k] = A1[i++];  // if left half contains next smallest item, merge it
      else A[k] = A2[j++];                // if right half contains next smallest item, merge it
   };

   // de-allocate memory
   delete[] A1;
   delete[] A2;
};

// Merge-sort process
void MergeSort(int * A, int left, int right, int M)
{
   if (left < right) {                 // if left index is not equal to right index
      int mid = (left + right) / 2;    // find (integer) midpoint
      MergeSort(A,left,mid,M);         // sort left half of array recursively
      MergeSort(A,mid+1,right,M);      // sort right half of array recursively
      Merge(A,left,mid,right,M);       // Merge two sorted halves
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
      for (int i = 0; i < N; i++) array[i] = rand() % M; // Generate random values
      MergeSort(array, 0, N-1, M);     // sort array
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

   MergeSort(array,0,N-1,M);  // sort array

   PrintArray(array,N,M);     // print array

   // Output status message
   if (CheckSort(array,N)) cerr << "Array sorted!" << endl;
   else cerr << "Array not sorted!" << endl;

   AutomatedTest(array,N,M);  // perform automated testing

   delete[] array;            // De-allocate memory
   return 0;                  // End of the program
};