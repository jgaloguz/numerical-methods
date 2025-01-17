// Heap-sort method for sorting array of integers

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

// Parent function
int Parent(int i) {return i / 2;}

// Left child function
int LeftChild(int i) {return 2 * i;}

// Right child function
int RightChild(int i) { return 2 * i + 1;}

// Function to make subtree rooted at i of input array a max heap
void MaxHeapify(int * A, int heapsize, int i) {
   int l = LeftChild(i);      // find left child of node i
   int r = RightChild(i);     // find right child of node i
   int max = i;               // i contains largest value by default

   if (l < heapsize && A[l] > A[max]) max = l;   // if left child is larger, set to exchange
   if (r < heapsize && A[r] > A[max]) max = r;   // if right child is larger, set to exchange
   if (max != i) {                               // if i does not contain largest value
      Swap(A+i,A+max);                          // swap i with largest
      MaxHeapify(A,heapsize,max);               // maxheapify on newly swapped child
   };
}

// Function to build a max heap from arbitrary array
void BuildMaxHeap(int * A, int heapsize) {
   // "Comb" the max heap from parents, to grand-parents, ..., to root
   for (int i = (heapsize/2)-1; i >= 0; i--) MaxHeapify(A,heapsize,i);
} 

// Heap-sort function
void HeapSort(int * A, int N) {
   BuildMaxHeap(A,N);            // convert input array into a max heap
   // loop right-to-left through generations from right-most child to left child of root
   for (int i = N-1; i >= 1; i--) {
      // sort by extracting root of successive subheaps and shortening relative heapsize
      Swap(A,A+i);               // root of sub-heap is largest element in A[0,..,i]
      MaxHeapify(A,i,0);         // maxheapify from the new root
   };
}

// Function to check if array is sorted
bool CheckSort(int * array, int N) {
   for (int i = 0; i < N-1; i++) {
      if (array[i] > array[i+1]) return false;  // if any elements out of order, return false
   };
   return true;                                 // if all elements in order, return true
}

// Function to print array
void PrintArray(int * array, int N, int M) {
   int n_digits = floor(log10(M) + 1.0) + 1;    // find width for output as number of digits possible plus 1 (for space)
   for (int i = 0; i < N; i++) cout << setw(n_digits) << array[i];
   cout << endl;
}

// Function for automatically test sorting function
void AutomatedTest(int * array, int N, int M) {
   int n_tests = 1000;                          // number of tests to perform
   int pass = 0;                                // number of tests passed
   for (int test = 0; test < n_tests; test++) {
      for (int i = 0; i < N; i++) array[i] = rand() % M;  // Generate random values
      HeapSort(array, N);              // sort array
      if (CheckSort(array,N)) pass++;  // if array was correctly sorted, add count it
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
      for (int i = 0; i < N; i++) array[i] = rand() % M;  // Generate random values
   } while (CheckSort(array,N));    // randomize values until array is not sorted

   PrintArray(array,N,M);     // print array

   HeapSort(array, N);        // sort array

   PrintArray(array,N,M);     // print array

   // Output status message
   if (CheckSort(array,N)) cerr << "Array sorted!" << endl;
   else cerr << "Array not sorted!" << endl;

   AutomatedTest(array,N,M);  // perform automated testing

   delete[] array;            // De-allocate memory
   return 0;                  // End of the program
}