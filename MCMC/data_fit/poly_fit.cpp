// MCMC applied to fitting data with polynomial model using a Bayesian maximum-likelihood approach

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

#define B 10000                     // Number of burn-in time iterations
#define I 100000                    // Number of Monte Carlo iterations

// Square function
inline double Sqr(double x) {return x*x;};

// Model to fit (polynomial)
double model(double x, double *a, int M)
{
   int i;                  // dummy index
   double y = a[M];        // output
// recursively compute y(x) = a_0 + x*(a_1 + x*(a_2 + x*(...)))
   for (i = 1; i <= M; i++) y = a[M-i] + x * y;
   return y;
};

// Prior distribution (uniform)
void prior(double *a, double *da, double *lb, double *ub, int M)
{
   int i;                  // dummy index
   for (i = 0; i <= M; i++) {
      a[i] = lb[i] + drand48() * (ub[i] - lb[i]);     // draw parameters from uniform distributions within specified bounds
      da[i] = 0.1 * (ub[i] - lb[i]);                  // determine maximum jump per step in the chain, ~10% of parameter range
   };
};

// Proposal distribution (uniform around current state)
bool proposal(double *a_new, double *a, double *da, double *lb, double *ub, int M)
{
   int i;                  // dummy index
   for (i = 0; i <= M; i++) {
      a_new[i] = a[i] + da[i] * (drand48() - 0.5);
// reject state automatically if its outside of prior range
      if (a_new[i] <= lb[i] || ub[i] <= a_new[i]) return false;
   };
   return true;
};

// Chi^2 of parameters | data
double Chi2(double *x, double *y, double *s, int N, double *a, int M)
{
   int i;                  // dummy index
   double chi2 = 0.0;      // Chi^2
   for (i = 0; i < N; i++) chi2 += Sqr((y[i] - model(x[i], a, M)) / s[i]);
   return chi2;
};

// Function to evolve the Markov Chain based on the Metropolis-Hastings algorithm
bool MarkovChain(double &chi2, double *a, double *da, double *lb, double *ub, int M, double *x, double *y, double *s, int N)
{
   int i;                  // dummy index
   double a_new[M];        // proposed state
   double chi2_new;        // proposed Chi^2

// Find proposed state and its Chi^2
   if (!proposal(a_new, a, da, lb, ub, M)) return false;
   chi2_new = Chi2(x, y, s, N, a_new, M);

// NOTE: By Bayes' Theorem, P(model|data) = P(model) * L(model) / P(data),
// where L(model,data) = P(data|model) = exp(-0.5*Chi^2(model,data))
// pi_j / pi_i = [P(model_j) * L(model_j,data)] / [P(model_i) * L(model_i,data)]
//             = L(model_j,data)]/ L(model_i,data), because P(model) = uniform (prior)
   double acc_prob = fmin(1.0, exp(0.5 * (chi2 - chi2_new)));  // acceptance probability (Metropolis-Hastings)

   if (drand48() < acc_prob) {                                 // if proposed state is accepted
      for (i = 0; i <= M; i++) a[i] = a_new[i];                // update state
      chi2 = chi2_new;                                         // update Chi^2
      return true;
   };
   return false;
};

int main() {
   int i, j;                        // dummy indices
   int N;                           // number of data points
   int M;                           // degree of model polynomial
   int A;                           // number of accepted proposed states
   double *x, *y, *s;               // data arrays
   double *a;                       // polynomial coefficients array
   double chi2;                     // Chi^2 for state
   double *lb, *ub;                 // bounds for parameter prior distribution
   double *da;                      // maximum jump in coefficients per step
   ifstream data_file;              // data file
   ofstream chain_file;             // chain file
   srand48(time(NULL));             // seed random number generator

// Input polynomial degree
   cout << "Polynomial degree for model: ";    // Ask for degree of polynomial model
   cin >> M;
   a = new double[M+1];
   lb = new double[M+1];
   ub = new double[M+1];
   da = new double[M+1];

// Input bounds
   for (i = 0; i <= M; i++) {
      cout << "For parameter of order " << i << endl;
      cout << "\tlower bound: ";
      cin >> lb[i];
      cout << "\tupper bound: ";
      cin >> ub[i];
   };
   cout << endl;

   data_file.open("data.txt");      // open data file

   data_file >> N;                  // input number of data points
   x = new double[N];               // independent coordinate
   y = new double[N];               // dependent coordinate
   s = new double[N];               // uncertainties

// Input data points
   for (i = 0; i < N; i++) {
      data_file >> x[i];
      data_file >> y[i];
      data_file >> s[i];
   };

   data_file.close();               // close data file

// Initialize quantities
   prior(a, da, lb, ub, M);         // Draw an initial state from the prior distribution
   chi2 = Chi2(x, y, s, N, a, M);   // Find Chi^2 for initial state

// Perform "burn-in" iterations
   for (i = 0; i < B; i++) MarkovChain(chi2, a, da, lb, ub, M, x, y, s, N);

// Draw from posterior distribution and output chain states to file
   chain_file.open("chain.txt");
   chain_file << setprecision(6);
   A = 0;                           // Reset accepted proposals counter
   for (i = 0; i < I; i++) {
      if (MarkovChain(chi2, a, da, lb, ub, M, x, y, s, N)) A += 1;
      for (j = 0; j <= M; j++) chain_file << setw(12) << a[j];
      chain_file << endl;
   };
   chain_file.close();
   cout << "Acceptance Ratio = " << (double)A / (double)I << endl;

   // Clean-up
   delete[] a;
   delete[] lb;
   delete[] ub;
   delete[] da;
   delete[] x;
   delete[] y;
   delete[] s;

   return 0; // End of the program
};