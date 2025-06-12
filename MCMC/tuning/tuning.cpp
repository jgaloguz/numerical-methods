// Tuning an MCMC based on heuristic quantities

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

#define D 0                         // Density to sample (0: 2D Gaussian; 1: rectangular uniform; 2: Rosenbrock)
#define S 0                         // Algorithm to use (0: Metropolis-Hastings; 1: stretch-move)
#define K 10                        // Number of walkers in stretch-move algorithm
#define B 1000                      // Number of burn-in time iterations
#define I 100000                    // Number of Monte Carlo iterations

const double twopi = 2.0 * M_PI;    // 2pi
const double Ki = 1.0 / (K-1);      // probability of drawing each walker of complementary ensemble

// Define paramater range
#if S == 0
const double param_low = 0.1;
const double param_high = 100.0;
#else
const double param_low = 1.1;
const double param_high = 1000.0;
#endif

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

// Integrated autocorrelation time
void AutocorrelationTimes(double *x, double *y, double &tau_x, double &tau_y)
{
   int i, j;
   double f, Cx, Cy;
   double Ex = 0.0, Ey = 0.0;
   double C0x = 0.0, C0y = 0.0;
   tau_x = 0.0;
   tau_y = 0.0;

// Expected values
   for (i = 0; i < I; i++) {
      Ex += x[i];
      Ey += y[i];
   };
   Ex /= (double)I;
   Ey /= (double)I;
// Zero lag
   for (i = 0; i < I; i++) {
      C0x += Sqr(x[i] - Ex);
      C0y += Sqr(y[i] - Ey);
   };
   C0x /= (double)I;
   C0y /= (double)I;
// Variable lag within a finite window (naive implementation)
   for (i = 1; i < 100; i++) {
      Cx = 0.0;
      Cy = 0.0;
      for (j = 0; j < I - i; j++) {
         Cx += (x[i + j] - Ex) * (x[j] - Ex);
         Cy += (y[i + j] - Ey) * (y[j] - Ey);
      };
      tau_x += Cx / (double)(I - i);
      tau_y += Cy / (double)(I - i);
   };

   tau_x *= 2.0 / C0x;
   tau_x += 1.0;
   tau_y *= 2.0 / C0y;
   tau_y += 1.0;
}

// Proposal function for Metropolis-Hastings (Gaussian)
inline void proposalMH(double &x, double &y, double sig)
{
// Generate two independent Gaussian random numbers (Box-Muller)
   double rad = sqrt(-2.0 * log(drand48()));
   double ang = twopi * drand48();
   double N1 = cos(ang) * rad;
   double N2 = sin(ang) * rad;

// 2D Gaussian centered around (x,y)
// Note: The covariance matrix is A*A^T where the coefficients of A are hard-coded below.
   x += sig * N1 + 0.0 * N2;
   y += 0.0 * N1 + sig * N2;
};

// Evolve chain for 1 step based on the Metropolis-Hastings algorithm
bool MetropolisHastings(double &x, double &y, double &log_dens, double sig)
{
   double xnew = x, ynew = y;

// Draw proposal state
   proposalMH(xnew, ynew, sig);
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

// Stretch density
inline double Stretch(double a)
{
   double sqrta = sqrt(a);
   return Sqr((sqrta - (1.0 / sqrta)) * drand48() + (1.0 / sqrta));
}

// Draw a walker from the complementary ensemble
inline int DrawWalker(int k)
{
   int i;
   double U = drand48();
   double sum = Ki;
   for (i = 0; i < k; i++) {
      if (U < sum) return i;
      else sum += Ki;
   };
   for (i = k+1; i < K; i++) {
      if (U < sum) return i;
      else sum += Ki;
   };
   return -1;  // error
}

// Evolve chain for 1 step based on the stretch-move algorithm
bool StretchMove(double *x, double *y, double *log_dens, double a)
{
   bool change = false;
   int i, j, A = 0;
   double z, xnew, ynew, log_dens_new;

// Iterate over all walkers
   for (i = 0; i < K; i++) {
// Draw proposal state
      j = DrawWalker(i);
      z = Stretch(a);
      xnew = x[j] + z * (x[i] - x[j]);
      ynew = y[j] + z * (y[i] - y[j]);
      log_dens_new = log(density(xnew, ynew));

// Accept or reject new state
      if (log(drand48()) < log(z) + log_dens_new - log_dens[i]) {
         x[i] = xnew;
         y[i] = ynew;
         log_dens[i] = log_dens_new;
         if (i == 0) change = true;
      };
   };

   return change;
};

int main() {
   int i, j;                        // dummy indices
   int Np = 10;                     // How many parameters to test
   int A;                           // acceptance counter
   double *x, *y;                   // components of (x,y) samples
   double log_dens[K];              // logarithm of density
   double xw[K], yw[K];             // components of (x,y) walkers
   double params[Np];               // number of parameters to test
   double acc[Np];                  // acceptance ratios
   double auto_x[Np], auto_y[Np];   // integrated autocorrelation times
   ofstream acceptance_file;        // acceptance ratio file
   ofstream autocorrelation_file;   // integrated autocorrelation time file
   srand48(time(NULL));             // seed random number generator

// Initialize arrays
   x = new double[I];
   y = new double[I];
   log_dens[0] = InitializeChain(x[0], y[0]);

   for(i = 0; i < Np; i++) {
// Status message
      cout << "Tunable parameter " << i+1 << endl;
// Find paramater from logarithmic range
      params[i] = exp(log(param_low) + i * log(param_high/param_low) / Np);
// Reset acceptance counter
      A = 0;

#if S == 0 // Metropolis-Hastings
// Burn-in time
      for (j = 0; j < B; j++) MetropolisHastings(x[0], y[0], log_dens[0], params[i]);
// Samples
      for (j = 1; j < I; j++) {
         x[j] = x[j-1];
         y[j] = y[j-1];
         if (MetropolisHastings(x[j], y[j], log_dens[0], params[i])) A += 1;
      };
#else // K-walkers stretch-move
// Initialize the other walkers
      for (j = 1; j < K; j++) {
         xw[j] = x[0];
         yw[j] = y[0];
         log_dens[j] = log_dens[0];
         while(!MetropolisHastings(xw[j], yw[j], log_dens[j], 1.0));
      };
// Burn-in time
      for (j = 0; j < B; j++) StretchMove(xw, yw, log_dens, params[i]);
// Samples. Record only the statistics of the first mover.
      for (j = 0; j < I; j++) {
         x[j] = xw[0];
         y[j] = yw[0];
         if (StretchMove(xw, yw, log_dens, params[i])) A += 1;
      };
#endif

// Compute acceptance ratio and integrated autocorrelation times
      cout << "Computing heuristics..." << endl;
      acc[i] = (double)A / (double)I;
      AutocorrelationTimes(x, y, auto_x[i], auto_y[i]);
   };

// Output results
   acceptance_file.open("acceptance.txt");
   acceptance_file << setprecision(6);
   acceptance_file << scientific;
   autocorrelation_file.open("autocorrelation.txt");
   autocorrelation_file << setprecision(6);
   autocorrelation_file << scientific;
   for (i = 0; i < Np; i++) {
      acceptance_file << setw(16) << params[i]
                      << setw(16) << acc[i]
                      << endl;
      autocorrelation_file << setw(16) << params[i]
                           << setw(16) << auto_x[i]
                           << setw(16) << auto_y[i]
                           << endl;
   };
   acceptance_file.close();
   autocorrelation_file.close();

// Clean-up
   delete[] x;
   delete[] y;

   return 0; // End of the program
};