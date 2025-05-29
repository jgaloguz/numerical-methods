// Solve the drift diffusion equation using both a forward and a backward stochastic method
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cstring>

// Simulation paramters
const double D = 1.0;                  // Diffusion coefficient
const double u = 1.0;                  // Drift coefficient
const double Ti = 0.5;                 // Initial time
const double Tf = 2.0;                 // Final time
const int Nt = 1000;                   // Number of time steps between 0 and Tf
const int Np = 10000;                  // Total number of particles

// Binning parameters
const double Xi = -10.0;               // Initial spatial coordinate for binning
const double Xf = 10.0;                // Final spatial coordinate for binning
const int Nx = 100;                    // Number of spatial bins

// Derived parameters
const double dt = Tf / (Nt - 1);       // Time resolution
const int Nt1 = Nt * (Ti / Tf);        // Time checkpoint 1 in number of steps
const int Nt2 = Nt - Nt1;              // Time checkpoint 2 in number of steps
const double dx = (Xf - Xi) / Nx;      // Spatial resolution
const double twopi = 2.0 * M_PI;       // 2pi

// Square function
inline double Sqr(double x) { return x * x; };

// Analytical solution
inline double Solution(double x, double t)
{
   return exp(-Sqr(x - u * t) / (4.0 * D * t)) / sqrt(M_PI * 4.0 * D * t);
};

// Normal distributed random number using Box-Muller method
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

// Bin event
void BinEvent(double event, double weight, double* x_distro, double* f_distro)
{
   if (event < x_distro[0]) f_distro[0] += weight;
   else if (event > x_distro[Nx]) f_distro[Nx-1] += weight;
   else f_distro[(int)((event-x_distro[0])/dx)] += weight;
};

int main(int argc, char** argv)
{
   int i,j,k;
   double V = u * dt, W = sqrt(2.0 * D * dt);
   double X1 = u * Tf - 3.0 * sqrt(2.0 * D * Tf);
   double X2 = u * Tf + 3.0 * sqrt(2.0 * D * Tf);
   double X[Nx+1], weight1 = 1.0 / dx / (double)Np;
   double forward1_distro[Nx], forward2_distro[Nx];
   double backward1_distro[Nx], backward2_distro[Nx];
   double particle1, particle2, x0, dX = X2-X1, sum;
   std::ofstream forward1_file, forward2_file;
   std::ofstream backward1_file, backward2_file;
   std::ofstream traj_forw_file, traj_back_file;

// Initialize random seed
   srand(time(NULL));

// Initialize particles and pseudo-particles
   for (i = 0; i < Nx; i++) {
      X[i] = Xi + i * dx;
      forward1_distro[i] = 0.0;
      forward2_distro[i] = 0.0;
      backward1_distro[i] = 0.0;
      backward2_distro[i] = 0.0;
   };
   X[Nx] = Xf;

   traj_forw_file.open("traj_forw.txt");
   traj_back_file.open("traj_back.txt");
// Iterate through particles
   for (i = 0; i < Np; i++) {
      std::cout << "\rParticle " << i;
// Initialize particle 1
      particle1 = 0.0;
// Propagate forward until Ti
      for (j = 0; j < Nt1; j++) particle1 += V + W * NormalRandom();
// Record
      BinEvent(particle1, weight1, X, forward1_distro);
// Propagate forward until Tf
      for (j = 0; j < Nt2; j++) {
         traj_forw_file << std::setw(20) << particle1;
         particle1 += V + W * NormalRandom();
      };
      traj_forw_file << std::setw(20) << particle1 << std::endl;
// Record
      BinEvent(particle1, weight1, X, forward2_distro);
// Initialize particle 2
      x0 = X1 + dX * drand48();
      particle2 = x0;
// Propagate backward until Ti
      for (j = 0; j < Nt2; j++) {
         particle1 -= V + W * NormalRandom();
         traj_back_file << std::setw(20) << particle2;
         particle2 -= V + W * NormalRandom();
      };
      traj_back_file << std::setw(20) << particle2 << std::endl;
// Record
      BinEvent(particle1, weight1, X, backward1_distro);
      BinEvent(x0, Solution(particle2,Ti), X, backward2_distro);
   };
   std::cout << "\rParticle " << Np << std::endl;

   traj_forw_file.close();
   traj_back_file.close();

// Normalize backward2_distro
   sum = 0.0;
   for (i = 0; i < Nx; i++) backward2_distro[i] /= (forward2_distro[i]+1.0e-15);
   for (i = 0; i < Nx; i++) sum += backward2_distro[i];
   sum *= dx;
   for (i = 0; i < Nx; i++) backward2_distro[i] /= sum;

// Output
   forward1_file.open("forward1.txt");
   forward2_file.open("forward2.txt");
   backward1_file.open("backward1.txt");
   backward2_file.open("backward2.txt");
   for (i = 0; i < Nx; i++) {
      forward1_file << forward1_distro[i] << std::endl;
      forward2_file << forward2_distro[i] << std::endl;
      backward1_file << backward1_distro[i] << std::endl;
      backward2_file << backward2_distro[i] << std::endl;
   };
   forward1_file.close();
   forward2_file.close();
   backward1_file.close();
   backward2_file.close();

   return 0;
};