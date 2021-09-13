// Solve Linear System of Equations using the Kaczmarz Algorithm

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

// get ||.||_2 error in current approximation
double error(double **A, double *b, double *x, int N) {
   double err = 0;      // error
   double dot;          // column multiplication
	for(int i = 0; i < N; i++) {
      dot = b[i];       // set value to b_i
      for(int j = 0; j < N; j++) {
         dot -= A[i][j] * x[j];  // subtract a_i dotted with x
      }
      err += dot*dot;   // square component
   }
   return sqrt(err);    // return norm 2 error
}

// dot row of A with x
double row_dot(double **A, double *x, int row, int N) {
   double dot = 0;      // dot product
   for(int j = 0; j < N; j++) dot += A[row][j] * x[j];
   return dot;
}

int main(void) {
   int i,j;             // dummy indices
   int N;               // size of the system
   int iter = 0;        // current iteration
   int max_iter = 1e6;  // maximum number of iterations (A LOT)
   int row;             // current row
   double **A;          // matrix
   double *row_norm2;   // norms (squared) of rows
   double *b;           // row vector
   double *x;           // approximate solution
   double scalar;       // dummy variable
   double eps = 1e-10;  // desired accuracy
   ifstream system;     // input file
   ofstream guesses;    // estimates at each iteration file

   system.open("system.txt");    // open system file

   system >> N;                  // input system dimension

   // Initialiaze matrix and independent coefficient vector
   A = create2D<double>(N,N);
   row_norm2 = new double[N];
   b = new double[N];
   x = new double[N];

   // Input matrix and vector values
   for(i = 0; i < N; i++) {
      row_norm2[i] = 0;
      for(j = 0; j < N; j++) {
         system >> A[i][j];
         row_norm2[i] += A[i][j] * A[i][j];  // update row squared values
      }
      system >> b[i];
      x[i] = 0;                  // set initial guess to 0
   }

   system.close();               // close system file

   // Iterate

   guesses.open("iterations.txt");     // open iterations file

   for(iter = 0; iter < max_iter; iter++) {
      // output current guess
      for(j = 0; j < N; j++) guesses << x[j] << " ";
      guesses << endl;
      if(error(A,b,x,N) < eps) break;  // break if solution is within desired accuracy
      row = iter % N;         // get row for current iteration
      scalar = (b[row] - row_dot(A,x,row,N)) / row_norm2[row];
      for(j = 0; j < N; j++) x[j] += scalar*A[row][j];     // update estimate
   }

   guesses.close();                    // close iterations file

   // output approximate solution, iterations, and accuracy
   if(iter == max_iter) {	// solution not found
      cout << "Solution could not be approximated to desired accuracy"
           << " within " << iter << " iterations..." << endl
           << "The current best guess is:" << endl;
      for(i = 0; i < N; i++) cout << x[i] << endl;
      cout << "with accuracy " << error(A,b,x,N) << endl;
   }
   else {			// solution found
      cout << "Solution approximated within " << iter << " iterations:" << endl;
      for(i = 0; i < N; i++) cout << x[i] << endl;
      cout << "with accuracy " << error(A,b,x,N) << endl;
   }

	// Clean-up
   delete2D(A,N,N);
   delete[] row_norm2;
   delete[] b;
   delete[] x;

   return 0;
}
