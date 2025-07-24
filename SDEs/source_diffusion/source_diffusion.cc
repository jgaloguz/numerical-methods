#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

// Simulation parameters
const double D = 0.5;                                 // Diffusion coefficient
const double Tf = 1.0;                                // Final time
const int Nt = 10000;                                 // Time steps
const int Np = 20000;                                 // Number of particles per grid point
const double LBC = 0.0;                               // left boundary value
const double RBC = 1.0;                               // right boundary value

// Binning parameters
const double Xi = -1.0;                               // Initial spatial coordinate for binning
const double Xf = 1.0;                                // Final spatial coordinate for binning
const int Nx = 40;                                    // Number of spatial bins for stochastic method
const int Nx_FD = Nx * 25;                            // Number of spatial bins for finite difference

// Derived parameters and constants
const double dt = Tf / Nt;                            // Time resolution
const double dx = (Xf - Xi) / Nx;                     // Spatial resolution for stochastic method
const double dx_FD = (Xf - Xi) / Nx_FD;               // Spatial resolution for finite difference
const double alpha = 0.5 * D * dt / dx_FD / dx_FD;    // finite difference parameter
const double twopi = 2.0 * M_PI;                      // 2pi

// Source function
inline double SrcTerm(double x) {
   if (-0.5 < x && x < 0.0) return 2.0;
   else return 0.0;
};

// Initial condition
inline double InitCond(double x) {return 0.5 * (1.0 + x);};

// Square function
inline double Sqr(double x) { return x * x; };

// Normal distributed random number
double NormalRandom()
{
   static bool roll = true;
   static double U1, U2;
   if (roll) {
      U1 = drand48();
      U2 = drand48();
      roll = false;
      return cos(twopi * U1) * sqrt(-2.0 * log(U2));
   }
   else {
      roll = true;
      return sin(twopi * U1) * sqrt(-2.0 * log(U2));
   };
};

// Thomas algorithm solver
void Thomas(int n, double *a, double *b, double *c, double *d)
{
   int i;
   double mult;
   for (i = 1; i < n; i++) { // eliminate a
      mult = a[i] / b[i - 1];
      b[i] -= c[i - 1] * mult;
      d[i] -= d[i - 1] * mult;
   };
   d[n - 1] /= b[n - 1]; // find solution
   for (i = n - 2; i >= 0; i--) d[i] = (d[i] - c[i] * d[i + 1]) / b[i];
};

int main(int argc, char** argv)
{
   int i,j,k;
   bool early_termination;
   double W = sqrt(2.0 * D * dt);
   double X[Nx+1], stochastic_distro[Nx+1];
   double X_FD[Nx_FD+1], finite_diff_distro[Nx_FD+1];
   double particle, amplitude, damp;
   double ldg[Nx_FD+1], dg[Nx_FD+1], udg[Nx_FD+1], rhs[Nx_FD+1];
   ofstream feynman_kac_file, crank_nicolson_file;
   ofstream amps_file, trajs_file;

// Initialize random seed
   srand(time(NULL));

// Stochastic solution
   cout << "Stochastic solution " << endl;
// Loop over grid locations and compute values
   X[0] = Xi;
   stochastic_distro[0] = LBC;
   for (i = 1; i < Nx; i++) {
      cout << "\rBin " << i;
      X[i] = Xi + i * dx;
      stochastic_distro[i] = 0.0;
// Open trajectories file in middle bin
      if (i == Nx / 2) {
         trajs_file.open("trajs.txt");
         amps_file.open("amps.txt");
      };
// Loop over particles
      for (j = 0; j < Np; j++) {
// Initialize trajectory
         particle = X[i];
         amplitude = 0.0;
         early_termination = false;
// Integrate trajectory
         for (k = 0; k <= Nt; k++) {
            if (i == Nx / 2) {
               trajs_file << setw(20) << particle;
               amps_file << setw(20) << amplitude;
            };
            amplitude += SrcTerm(particle) * dt;
            particle += W * NormalRandom();
// Bin particle on right boundary (if necessary)
            if (particle >= 1.0) {
               stochastic_distro[i] += RBC + amplitude;
               early_termination = true;
               break;
            }
// Bin particle on left boundary (if necessary)
            else if (particle <= -1.0) {
               stochastic_distro[i] += LBC + amplitude;
               early_termination = true;
               break;
            };
         };
         if (i == Nx / 2) {
            trajs_file << setw(20) << particle << endl;
            amps_file << setw(20) << amplitude << endl;
         };
// Bin particle on time boundary (if necessary)
         if (!early_termination) stochastic_distro[i] += InitCond(particle) + amplitude;
      };
// Close trajectories file in middle bin
      if (i == Nx / 2) {
         trajs_file.close();
         amps_file.close();
      };
// Normalize value
      stochastic_distro[i] /= Np;
   };
   X[Nx] = Xf;
   stochastic_distro[Nx] = RBC;
   cout << endl;

// Output
   feynman_kac_file.open("feynman_kac.txt");
   for (i = 0; i <= Nx; i++) {
      feynman_kac_file << setw(16) << X[i]
                       << setw(16) << stochastic_distro[i]
                       << endl;
   };
   feynman_kac_file.close();

// Finite difference solution
   cout << "Finite difference solution" << endl;
// Set initial condition
   X_FD[0] = Xi;
   finite_diff_distro[0] = LBC;
   for (i = 1; i < Nx_FD; i++) {
      X_FD[i] = Xi + i * dx_FD;
      finite_diff_distro[i] = InitCond(X_FD[i]);
   };
   X_FD[Nx_FD] = Xf;
   finite_diff_distro[Nx_FD] = RBC;
// Loop over time
   for (k = 0; k <= Nt; k++) {
// Build triadiagonal matrix system
      ldg[0] = 0.0; // unused
      dg[0] = 1.0;
      udg[0] = 0.0;
      rhs[0] = LBC;
      for (i = 1; i < Nx_FD; i++) {
         ldg[i] = -alpha;
         dg[i] = (1.0 + 2.0 * alpha);
         udg[i] = -alpha;
         rhs[i] = alpha * finite_diff_distro[i-1]
                + (1.0 - 2.0 * alpha) * finite_diff_distro[i]
                + alpha * finite_diff_distro[i+1]
                + SrcTerm(X_FD[i]) * dt;
      };
      ldg[Nx_FD] = 0.0;
      dg[Nx_FD] = 1.0;
      udg[Nx_FD] = 0.0; // unused
      rhs[Nx_FD] = RBC;

// Solve system
      Thomas(Nx_FD+1, ldg, dg, udg, rhs);
      memcpy(finite_diff_distro, rhs, (Nx_FD+1)*sizeof(double));
   };

   crank_nicolson_file.open("crank_nicolson.txt");
   for (i = 0; i <= Nx_FD; i++) {
      crank_nicolson_file << setw(16) << X_FD[i]
                          << setw(16) << finite_diff_distro[i]
                          << endl;
   };
   crank_nicolson_file.close();
   return 0;
};