// Monte Carlo method to estimate the area of a circle

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

#define N 1000                               // number of samples per trial
#define M 100                                // number of MC trials

// Square function
inline double Sqr(const double x) {return x*x;};

const double R = 1.0;                        // radius of circle
const double R2 = Sqr(R);                    // square of radius
const double A = M_PI * R2;                  // area of circle
const double B = Sqr(2.0 * R);               // area of rectangle
const double EX = A;                         // expected value of area function
const double EX2 = B * A;                    // expected value of area function squared
const double var = EX2 - Sqr(EX);            // variance of area function

// Function to generate random variable for average
double RandVar()
{
   double x = -R + 2.0 * R * drand48();
   double y = -R + 2.0 * R * drand48();
   return (Sqr(x) + Sqr(y) < R2 ? B : 0.0);
};

int main() {
   int i, j, k;                              // dummy indices
   double C;                                 // MC count
   double error[N] = {0.0};                  // average error
   srand48(time(NULL));                      // seed random number generator
   ofstream error_file;                      // error file

// Loop over realizations
   for (j = 0; j < M; j++) {
      C = 0.0;
// Loop over samples
      for (i = 0; i < N; i++) {
         C += RandVar();
         error[i] += Sqr(A - C / (double)(i+1));
      };
   };
// Normalize error
   for (i = 0; i < N; i++) error[i] = sqrt(error[i] / M);

// Output theoretical and simulation error
   error_file.open("error.txt");
   for (i = 0; i < N; i++) {
      error_file << setw(12) << i+1
                 << setw(12) << sqrt(var / (i+1))
                 << setw(12) << error[i]
                 << endl;
   };
   error_file.close();

// Print estimate of area
   cout << "Area = " << C / (double)N << endl;
  
   return 0; // End of the program
};
