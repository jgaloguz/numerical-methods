// Solve Linear System of Equations using Gauss-Jordan Elimination

#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

// Create 2D array template
template <class T> T **create2D(int h, int w)
{
   T **array = new T*[h];
   for (int i = 0; i < h; i++) array[i] = new T[w];
   return array;
};

// Delete 2D array template
template <class T> void delete2D(T **array, int h, int w)
{
   for (int i = 0; i < h; i++) delete[] array[i];
   delete[] array;
};

// Matrix solver using Gauss-Jordan elimination
void gauss_jordan(double **A, double *b, int N)
{
   int i,j,k,l;            // dummy indices
   int *order;             // array with order of rows
   double max;             // largest row element
   double x,y;             // dummy variables
   double *c;              // array with ordered solution

   // Initialize order
   order = new int[N];
   for (i = 0; i < N; i++) order[i] = i;

   // Loop over columns
   for (j = 0; j < N-1; j++) {
      // Find largest (in magnitude) column element
      max = fabs(A[order[j]][j]);
      k = j;
      for (i = j + 1; i < N; i++) {
         x = fabs(A[order[i]][j]);
         if (x > max) {
            max = x;
            k = i;
         };
      };

      // Update the row order
      l = order[j];
      order[j] = order[k];
      order[k] = l;

      // Subtract the pivot row (j) from row i
      for (i = j + 1; i < N; i++) {
         y = A[order[i]][j] / A[order[j]][j];
         for (l = j + 1; l < N; l++) A[order[i]][l] -= y * A[order[j]][l];
         b[order[i]] -= y * b[order[j]];
      };
      // Notice all the elements directly below A[j][j] are ignored
      // in the second for loop since they are going to cancel anyways.
      // This saves us a few operations.
   };

   // Backward substitution loop
   b[order[N - 1]] /= A[order[N - 1]][N - 1];
   for (i = N - 2; i >= 0; i--) {
      for (j = i + 1; j < N; j++) b[order[i]] -= A[order[i]][j] * b[order[j]];
      b[order[i]] /= A[order[i]][i];
   };

   // Reorder the solution vector
   c = new double[N];
   for (i = 0; i < N; i++) c[i] = b[order[i]];
   for (i = 0; i < N; i++) b[i] = c[i];

   // clean-up
   delete[] order;
   delete[] c;
};

int main(void) {
   int i,j;          // dummy indices
   int N;            // size of the system
   double **A;       // matrix
   double *b;        // row vector
   ifstream system;  // input file

   system.open("system.txt");    // open system file

   system >> N;                  // input system dimension

   // Initialiaze matrix and independent coefficient vector
   A = create2D<double>(N,N);
   b = new double[N];

   // Input matrix and vector values
   for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) system >> A[i][j];
      system >> b[i];
   };

   system.close();               // close system file

   gauss_jordan(A,b,N);          // solve system

   // output solution
   cout << "solution:" << endl;
   for (i = 0; i < N; i++) cout << b[i] << endl;

   // Clean-up
   delete2D(A,N,N);
   delete[] b;

   return 0;
};
