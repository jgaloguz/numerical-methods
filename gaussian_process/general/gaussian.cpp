// Simulate a Gaussian process given its mean and covariance function

#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <Eigen/Dense>

using namespace std;

constexpr double M_2PI = 2.0 * M_PI;

// Square function
inline double Sqr(double x) {return x*x;};

// Create 2D lower-triangular array template
template <class T> T **create2Dlower(int h)
{
   T **array = new T*[h];
   for (int i = 0; i < h; i++) array[i] = new T[i+1];
   return array;
};

// Delete 2D lower-triangular array template
template <class T> void delete2Dlower(T **array, int h)
{
   for (int i = 0; i < h; i++) delete[] array[i];
   delete[] array;
};

// Print lower-triangular matrix
template <class T> void PrintLower(T **array, int h)
{
   cout << setprecision(8);
   for (int i = 0; i < h; i++) {
      for (int j = 0; j <= i; j++) cout << setw(18) << array[i][j];
      cout << endl;
   };
};

// Generate (two independent) normally distributed random numbers using the Box-Muller method
double BoxMuller()
{
   static int i = 0;       // even/odd counter for efficiency
   static double U[2];     // uniform random values
   if (i % 2) {            // odd iteration (reuse uniform random values)
      return sqrt(-2.0 * log(U[0])) * cos(M_2PI * U[1]);
   }
   else {                  // even iteration (generate uniform random values)
      U[0] = drand48();
      U[1] = drand48();
      return sqrt(-2.0 * log(U[0])) * sin(M_2PI * U[1]);
   };
};

// Check eigenvalues for a symmetric matrix and check if they are positive (requires Eigen library)
void CheckEigenValues(double **A, int N)
{
#ifdef EIGEN_CORE_MODULE_H
   int i,j;       // dummy indices
// Load symmetric matrix from lower triangular matrix
   Eigen::MatrixXd A_full(N,N);
   for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
         if (i < j) A_full(i,j) = A[j][i];
         else A_full(i,j) = A[i][j];
      };
   };
// Compute eigen values and check
   Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> ev(A_full);
   Eigen::VectorXd eigenvalues = ev.eigenvalues();
   for (i = 0; i < N; i++) {
      if (eigenvalues(i) < 0.0) {
         cerr << "WARNING: Negative eigenvalues detected." << endl
              << "\tCovariance matrix is NOT positive-definite to machine precision." << endl
              << "\tCholesky decomposition will likely fail." << endl;
         break;
      };
   };
#endif
};

// Cholesky–Banachiewicz algorithm to find L such that A = L*L^T where A is symmetric, positive-definite
void CholeskyDecomp(double **L, double **A, int size)
{
   int i,j,k;     // dummy indices
   double sum;    // running sum
   for (i = 0; i < size; i++) {
      for (j = 0; j <= i; j++) {
         sum = 0.0;
         for (k = 0; k < j; k++) sum += L[i][k] * L[j][k];

         if (i == j) L[i][j] = sqrt(A[i][i] - sum);
         else L[i][j] = (A[i][j] - sum) / L[j][j];
      };
   };
};

// Mean function of gaussian process
inline double Mean(double t)
{
   return 0.0;
};

// Covariance function of gaussian process. It MUST be symmetric with respect to `t1` and `t2`.
inline double Cov(double t1, double t2)
{
   return fmin(t1, t2);                // Wiener process
   // return exp(-fabs(t1-t2));           // Abel kernel (Ornstein-Uhlenbeck)
   // return exp(-0.5 * Sqr(t1-t2));      // Gaussian kernel
};

int main(void) {
   int i,j;                            // dummy indices
   int N;                              // number of time points
   double Tf;                          // final time to simulate
   double dT;                          // time step
   double X;                           // realization of Gaussian process
   double *T;                          // vector of times
   double *m;                          // mean vector
   double *g;                          // iid sequence of normally distributed random variables
   double **B;                         // covariance matrix
   double **L;                         // "square root" of covariance matrix
   ofstream process_file;              // output file
   srand48(time(NULL));                // seed random number generator

// Input simulation parameters
   cout << "Time to simulate: ";       // Ask for total simulation time
   cin >> Tf;
   cout << "Number of points: ";       // Ask for number of time points
   cin >> N;

// Allocate memory
   T = new double[N];
   m = new double[N];
   g = new double[N];
   B = create2Dlower<double>(N);
   L = create2Dlower<double>(N);

// Load time, mean function, and iid sequence arrays
   dT = Tf / N;
   for (i = 0; i < N; i++) {
      T[i] = (i+1) * dT;
      m[i] = Mean(T[i]);
      g[i] = BoxMuller();
   };
// Load covariance matrix
   for (i = 0; i < N; i++) {
      for (j = 0; j <= i; j++) {
         B[i][j] = Cov(T[i],T[j]);
      };
   };

// Check eigenvalues (requires Eigen libray)
   CheckEigenValues(B,N);

// Find "square root" (Cholesky decomposition) of covariance matrix
// NOTE: This is a numerically unstable for ill-conditioned B's
   CholeskyDecomp(L,B,N);
   // PrintLower(B,N);
   // PrintLower(L,N);

// Simulate process
   process_file.open("gaussian.txt");
   process_file << setprecision(8);
   process_file << setw(16) << 0.0
                << setw(16) << Mean(0.0)
                << endl;
   for (i = 0; i < N; i++) {
      X = Mean(T[i]);
      for (j = 0; j <= i; j++) X += L[i][j] * g[j];
      process_file << setw(16) << T[i]
                   << setw(16) << X
                   << endl;
   };
   process_file.close();

// Clean-up
   delete[] T;
   delete[] m;
   delete[] g;
   delete2Dlower(B, N);
   delete2Dlower(L, N);

   return 0;         // end of program
};