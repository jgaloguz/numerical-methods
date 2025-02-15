// Test strong convergence of different numerical methods to solve SDEs
#include <iostream>
#include <iomanip>
#include <cmath>
#include <random>
#include <ctime>

#define MODE 1 // MODE == 1: print sample trajectories; MODE == 2: compute strong and weak errors
#define METHOD 1 // METHOD == 1: Euler-Maruyama; METHOD == 2: Milstein; METHOD == 3: RK2; METHOD == 4: stochastic theta (semi-implicit)
// Note: Tocino & Ardunay (2002) also give a 2-stage RK method valid when db/dx = constant (eq. 35), different from the general RK2 method (eq. 41).

// Square function
inline double Sqr(double x) {return x * x;};

// Model parameters
const double r = 1.0;                              // drift constant
const double alpha = 0.5;                          // diffusion constant
const double alpha2 = Sqr(alpha);                  // square of diffusion constant
const double beta = r - 0.5 * alpha * alpha;       // combined exponent of solution
const double GBM0 = 1.0;                           // initial point

// Simulation parameters
const int R = 100000;                              // Number of realizations
const int R_10 = R / 10;                           // Output interval
const int N = 10001;                               // Number of time steps per trajectory
const int n_res = 4;                               // Number of resoluations for convergence tests
const int N_res[n_res] = {21, 101, 501, 2501};     // Number of steps per resolution
const double T = 1.0;                              // Final time to simulate

// Various constants for the RK2 and stochastic theta methods
const double gam = 1.0 / 3.0;
const double one_3gam = 1.0 / 3.0 / gam;
const double rat1 = 1.0 / (2.0 + 6.0 * Sqr(gam));
const double rat2 = 3.0 * Sqr(gam) * rat1;
const double theta = 0.5;
const double one_mnst = 1.0 - theta;

// Function to interpolate f(y) were y is a value between x[low] and x[N-1]
double Interp(double *f, double *x, double y, int &low)
{
   if (y >= x[N-1]) return f[N-1];

   int i1, i2, i3;
   i1 = i2 = low;
   i3 = N-1;

// Bisection algorithm to find left index of interval containing value
   while (i3 - i1 > 1) {
      i2 = (i1 + i3) >> 1;
      (y > x[i2] ? i1 : i3) = i2;
   };
   low = i1;
   i2 = i1+1;

   return (f[i1] * (x[i2] - y) + f[i2] * (y - x[i1])) / (x[i2] - x[i1]);
};

// Multiplicative factor to advance solution by one step
inline double Growth(double dt, double dW)
{
   double factor;
#if METHOD == 1
   factor = 1.0 + r * dt + alpha * dW;
#elif METHOD == 2
   factor = 1.0 + r * dt + alpha * dW + 0.5 * alpha2 * (Sqr(dW) - dt);
#elif METHOD == 3
   double GBM1, GBM2, GBM3;
   GBM1 = 1.0 + r * dt + gam * alpha * dW;
   GBM2 = 1.0 + r * dt - one_3gam * alpha * dW;
   GBM3 = 1.0 + r * dt + alpha * dW;
   factor = 1.0 + 0.5 * r * (1.0 + GBM3) * dt
                + alpha * (0.5 + rat1 * GBM1 + rat2 * GBM2) * dW
                + 0.5 * alpha2 * (Sqr(dW) - dt);
#elif METHOD == 4
   factor = (1.0 + one_mnst * dt + alpha * dW) / (1 - theta * r * dt);
#endif
   return factor;
};

// Integrate one trajectory using a realization of a Weiner process
double IntegrateOne(double *t, double *W, double dt, double N, bool print)
{
   int i;                     // dummy index
   int j = 0;                 // index to speed up interpolation
   double GBM = GBM0;         // process to numerically integrate
   double s = 0.0;            // time to interpolate pre-realized Weiner process
   double U, V = W[0];        // next and last interpolated values
   for (i = 1; i < N; i++) {
      if (print) std::cout << std::setw(16) << s
                           << std::setw(16) << GBM
                           << std::endl;
      s += dt;
      U = Interp(W,t,s,j);
      GBM *= Growth(dt, U - V);
      V = U;
   };
   if (print) std::cout << std::setw(16) << s
                        << std::setw(16) << GBM
                        << std::endl;

   return GBM;
};

int main(void)
{
   int i,j;
   double t[N];
   double W[N];
   double dt_min = T / (N-1);
   double dt_res[n_res];
   double *GBMT;
   double *GBMT_num[n_res];
   double mu, strong_mu[n_res], weak_mu[n_res];
   double sig, strong_sig[n_res], weak_sig[n_res];

// Allocate memory
   GBMT = new double[R];
   for (i = 0; i < n_res; i++) {
      dt_res[i] = T / (N_res[i]-1);
      GBMT_num[i] = new double[R];
   };

// RNG stuff
   std::default_random_engine generator;
   generator.seed(time(NULL));
   std::normal_distribution<double> distribution(0.0,sqrt(dt_min));

#if MODE == 1

// Generate Wiener process
   t[0] = 0.0;
   W[0] = 0.0;
   for (i = 1; i < N; i++) {
      t[i] = i * dt_min;
      W[i] = W[i-1] + distribution(generator);
   };

// Output Weiner process and GBM realized with it
   std::cout << std::setprecision(8);
   for (i = 0; i < N; i++) {
      std::cout << std::setw(16) << t[i]
                << std::setw(16) << GBM0 * exp(beta * t[i] + alpha * W[i])
                << std::endl;
   };
   std::cout << std::endl;

// Numerically solve GBM
   for (i = 0; i < n_res; i++) {
      IntegrateOne(t, W, dt_res[i], N_res[i], true);
      std::cout << std::endl;
   };

#elif MODE == 2

   std::cerr << "0% complete" << std::endl;
   for (j = 0; j < R; j++) {
      if ((j+1) % R_10 == 0) std::cerr << 100*(j+1)/R << "% complete" << std::endl;

// Generate Wiener process and GBM
      t[0] = 0.0;
      W[0] = 0.0;
      for (i = 1; i < N; i++) {
         t[i] = i * dt_min;
         W[i] = W[i-1] + distribution(generator);
      };
      GBMT[j] = GBM0 * exp(beta * t[N-1] + alpha * W[N-1]);

// Numerically solve GBM
      for (i = 0; i < n_res; i++) GBMT_num[i][j] = IntegrateOne(t, W, dt_res[i], N_res[i], false);
   };

// Compute averages
   mu = 0;
   for (j = 0; j < R; j++) mu += GBMT[j];
   mu /= R;

   for (i = 0; i < n_res; i++) {
      strong_mu[i] = 0.0;
      weak_mu[i] = 0.0;
      for (j = 0; j < R; j++) {
         strong_mu[i] += fabs(GBMT_num[i][j] - GBMT[j]);
         weak_mu[i] += GBMT_num[i][j];
      };
      strong_mu[i] /= R;
      weak_mu[i] /= R;
   };

// Compute standard deviations
   sig = 0.0;
   for (j = 0; j < R; j++) sig += Sqr(GBMT[j] - mu);
   sig = sqrt(sig / R);

   for (i = 0; i < n_res; i++) {
      strong_sig[i] = 0.0;
      weak_sig[i] = 0.0;
      for (j = 0; j < R; j++) {
         strong_sig[i] += Sqr(fabs(GBMT_num[i][j] - GBMT[j]) - strong_mu[i]);
         weak_sig[i] += Sqr(GBMT_num[i][j] - weak_mu[i]);
      };
      strong_sig[i] = sqrt(strong_sig[i] / R);
      weak_sig[i] = sqrt(weak_sig[i] / R);
   };

// Output results
   for (i = 0; i < n_res; i++) {
      std::cout << std::setw(16) << dt_res[i]
                << std::setw(16) << strong_mu[i]
                << std::setw(16) << strong_sig[i] / R
                << std::setw(16) << fabs(weak_mu[i] - mu)
                << std::setw(16) << (weak_sig[i] + sig) / R
                << std::endl;
   };
   std::cerr << std::endl;
   std::cerr << std::setw(16) << dt_min
             << std::setw(16) << mu
             << std::setw(16) << sig
             << std::endl;

#endif

// Free memory
   delete[] GBMT;
   for (i = 0; i < n_res; i++) delete[] GBMT_num[i];

   return 0;
};

