// Solve an SDE with the Euler-Maruyama method
#include <iostream>
#include <iomanip>
#include <cmath>
#include <random>
#include <fstream>

using namespace std;

// Square function
inline double Sqr(double x) {return x * x;};

// Simulation parameters
#define R 10000                                 // Number of realizations
#define N 1001                                  // Number of time steps per trajectory

const double twopi = 2.0 * M_PI;                // 2pi

// Normal distributed random number using Box-Muller method
double NormalRandom(void)
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

int main(void)
{
   int i,j;                            // dummy indices
   double t;                           // current time
   double f;                           // frequency
   double X;                           // current position
   double V;                           // current velocity
   double m;                           // mass
   double y;                           // damping factor
   double k;                           // spring constant
   double s;                           // white noise factor
   double T;                           // final time to simulate
   double dt;                          // time step
   double sqrtdt;                      // square root of time step
   double df;                          // frequency step
   double dW;                          // Wiener increment
   double EX[N] = {0};                 // expected first momentum
   double EX2[N] = {0};                // expected second momentum
   ofstream traj_file;                 // file with sample trajectories
   ofstream avgs_file;                 // file with averages
   ofstream spec_file;                 // file with spectrum
   srand48(time(NULL));                // seed random number generator

// Input simulation parameters
   cout << "Mass: ";                   // Ask for mass
   cin >> m;
   cout << "Damping factor: ";         // Ask for damping factor
   cin >> y;
   cout << "Spring constant: ";        // Ask for spring constant
   cin >> k;
   cout << "White noise factor: ";     // Ask for white noise factor
   cin >> s;
   cout << "Time to simulate: ";       // Ask for total simulation time
   cin >> T;
// Compute times for average
   dt = T / (N-1);                     // time step between outputs
   sqrtdt = sqrt(dt);                  // square root of time step
   df = 5.0 *sqrt(k / m) / (N-1);      // Frequency step

// Iterate over realizations
   for (i = 0; i < R; i++) {
// Iterate over time
      t = 0.0;
      X = 0.0;
      V = 0.0;
      for (j = 0; j < N; j++) {
         EX[j] += X;
         EX2[j] += Sqr(X);
         dW = sqrtdt * NormalRandom();
         X += V * dt;
         V += (- (k * X + y * V) * dt + s * dW) / m;
         t += dt;
      };
   };
// Normalize averages
   for (j = 0; j < N; j++) {
      EX[j] /= R;
      EX2[j] /= R;
   };

// Output sample trajectories
   traj_file.open("trajectory.txt");
   t = 0.0;
   X = 0.0;
   V = 0.0;
   for (j = 0; j < N; j++) {
      traj_file << setw(20) << t
                << setw(20) << X
                << endl;
      dW = sqrtdt * NormalRandom();
      X += V * dt;
      V += (- (k * X + y * V) * dt + s * dW) / m;
      t += dt;
   };
   traj_file.close();

// Output averages
   avgs_file.open("moments.txt");
   t = 0.0;
   for (j = 0; j < N; j++) {
      avgs_file << setw(20) << t
                << setw(20) << EX[j]
                << setw(20) << sqrt(EX2[j] - Sqr(EX[j]))
                << endl;
      t += dt;
   };
   avgs_file.close();

// Output spectral density
   spec_file.open("spectrum.txt");
   f = 0.0;
   for (j = 0; j < N; j++) {
      spec_file << setw(20) << f
                << setw(20) << Sqr(s) / twopi / (Sqr(m * Sqr(f) - k) + Sqr(y * f)) 
                << endl;
      f += df;
   };
   spec_file.close();
   cout << "Resonant frequency: " << sqrt(k / m) << endl;

   return 0; // End of the program
};

