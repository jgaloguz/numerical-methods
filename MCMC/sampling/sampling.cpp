// MCMC applied to sampling from a known density function

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

#define D 0                         // Density to sample (0: 2D Gaussian; 1: rectangular uniform; 2: Rosenbrock)
#define B 1000                      // Number of burn-in time iterations
#define I 100000                    // Number of Monte Carlo iterations

const double twopi = 2.0 * M_PI;    // 2pi

// Square function
inline double Sqr(double x) {return x*x;};

// Density function (unnormalized)
inline double density(double x, double y)
{
#if D == 0
   return exp(- 0.5 * (0.78 * Sqr(x) - 2.0 * 0.47 * x * y + 0.78 * Sqr(y)));
#elif D == 1
   return ((3.0 < x) && (x < 7.0) && (1.0 < y) && (y < 9.0) ? 1.0 : 0.0);
#else
   return exp(- 0.05 * (100.0 * Sqr(y - Sqr(x)) + Sqr(1.0 - x)));
#endif
};

// Initialize chain
inline double InitializeChain(double &x, double &y)
{
#if D == 0
   x = 0.0;
   y = 0.0;
#elif D == 1
   x = 5.0;
   y = 5.0;
#else
   x = 0.0;
   y = 0.0;
#endif
   return log(density(x,y));
};

// Proposal function (Gaussian)
inline void proposal(double &x, double &y)
{
// Generate two independent Gaussian random numbers (Box-Muller)
   double rad = sqrt(-2.0 * log(drand48()));
   double ang = twopi * drand48();
   double N1 = cos(ang) * rad;
   double N2 = sin(ang) * rad;

// 2D Gaussian centered around (x,y)
// Note: The covariance matrix is A*A^T where the coefficients of A are hard-coded below.
   x += 1.0 * N1 + 0.0 * N2;
   y += 0.0 * N1 + 1.0 * N2;
};

// Evolve chain for 1 step based on the Metropolis-Hastings algorithm
bool MetropolisHastings(double &x, double &y, double &log_dens)
{
   double xnew = x, ynew = y;

// Draw proposal state
   proposal(xnew, ynew);
   double log_dens_new = log(density(xnew, ynew));

// Accept or reject new state
   if (log(drand48()) < (log_dens_new - log_dens)) {
      x = xnew;
      y = ynew;
      log_dens = log_dens_new;
      return true;
   }
   else return false;
};

int main() {
   int i, j;                        // dummy indices
   int A = 0;                       // number of accepted proposed states
   double x, y;                     // components of (x,y) samples
   double log_dens;                 // logarithm of density
   ofstream chain_file;             // chain file
   srand48(time(NULL));             // seed random number generator

// Initialize chain and perform "burn-in" iterations
   log_dens = InitializeChain(x, y);
   for (i = 0; i < B; i++) MetropolisHastings(x, y, log_dens);

// Draw from posterior distribution and output chain states to file
   chain_file.open("chain.txt");
   chain_file << setprecision(6);
   chain_file << scientific;
   for (i = 0; i < I; i++) {
      if (MetropolisHastings(x, y, log_dens)) A += 1;
      chain_file << setw(16) << x
                 << setw(16) << y
                 << endl;
   };
   chain_file.close();
   cout << "Acceptance Ratio = " << (double)A / (double)I << endl;

   return 0; // End of the program
};