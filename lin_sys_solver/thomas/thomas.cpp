// Solve Banded Linear System of Equations using Thomas Algorithm

#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

// Define create 2D array template
template <class T> T **create2D(int h, int w) {
   T **array = new T*[h];
   for(int i = 0; i < h; i++) array[i] = new T[w];
   return array;
}

// Define delete 2D array template
template <class T> void delete2D(T **array, int h, int w) {
   for(int i = 0; i < h; i++) delete[] array[i];
   delete[] array;
}

// Bandwidth matrix solver using the Thomas algorithm
void thomas(double **A, double *b, double *x, int N, int bandwidth)
{
   int i,j,k,top,bot;   // indices
   double mult;         // factor

   // eliminate lower diagonals
   for(i = 0; i < N-1; i++) {                           // iterate through columns
      top = i+1;                                        // lowest row value to eliminate for this column
      bot = (i < N-bandwidth ? top+bandwidth : N);      // highest row value to eliminate for this column
      for(j = top; j < bot; j++) {                      // iterate through row values within bandwidth
         mult = A[j][i] / A[i][i];                      // find cancelation factor
         for(k = top; k < bot; k++) {                   // iterate through column values within bandwidth
            A[j][k] -= A[i][k] * mult;                  // perform row operations on matrix
         }
         b[j] -= b[i] * mult;                           // perform row operations on vector
      }
   }

   // find solution
   x[N-1] = b[N-1] / A[N-1][N-1];                       // find last x value
   for(i = N-2; i >= 0; i--) {                          // iterate over all rows
      top = i+1;                                        // lowest non-zero column value for this row
      bot = (i > N-bandwidth-1 ? N : top+bandwidth);    // highest non-zero column value for this row
      for(j = top; j < bot; j++) {                      // iterate through columns
         b[i] -= A[i][j] * x[j];                        // isolate unknown variable to solve for within bandwidth
      }
      x[i] = b[i] / A[i][i];                            // solve for unknown variable on diagonal
   }
}

int main(void) {
   int i,j;          // dummy indices
   int N;            // size of the system
   int bandwidth;    // bandwidth of the system
   double **A;       // matrix
   double *b;        // row vector
   double *x;        // solution vector
   ifstream system;  // input file

   system.open("system.txt");    // open system file

   system >> N;                  // input system dimension
   system >> bandwidth;          // input system bandwidth

   // Initialiaze matrix and independent coefficient vector
   A = create2D<double>(N,N);
   b = new double[N];
   x = new double[N];

   // Input matrix and vector values
   for(i = 0; i < N; i++) {
      for(j = 0; j < N; j++) {
         system >> A[i][j];
      }
      system >> b[i];
   }

   system.close();               // close system file

   thomas(A,b,x,N,bandwidth);    // solve system

   // output solution
   cout << "solution:" << endl;
   for(i = 0; i < N; i++) cout << x[i] << endl;

	// Clean-up
   delete2D(A,N,N);
   delete[] b;
   delete[] x;

   return 0;
}
