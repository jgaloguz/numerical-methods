// Synthesis-Decomposition reaction as a continuous-time Markov chain

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

#define T 10.0                      // Final time to simulate
#define N 1000                      // Number of times to discretize realization between 0 and T

const double twopi = 2.0 * M_PI;    // 2pi

// Poisson random variable with rate lambda
inline int Poisson(double lambda)
{
   double U = drand48();
   int k = 0;
   double e_rate = exp(-lambda);
   double term = 1.0, CDF = 1.0;
   while (U > CDF * e_rate) {
      k++;
      term *= lambda / k;
      CDF += term;
   };
   return k;
};

// Cauchy random variable with location 0 and scale 1 / dt.
inline double Cauchy(double dt) {return tan(M_PI * (drand48() - 0.5)) / dt;};

// Gaussian random variable with mean 0 and variance dt
inline double Normal(double dt)
{
   static int draw = 0;
   static double rad, ang;
   double normal;

// Box-Muller generates 2 independent samples
   if (draw % 2 == 0) {
      rad = sqrt(-2.0 * log(drand48()));
      ang = twopi * drand48();
      normal = cos(ang) * rad;
   }
   else normal = sin(ang) * rad;

   draw += 1;
   return normal;
};

// Increment Law
double Increment(double dt) 
{
   return Poisson(1.0 * dt); // Poisson increments
   // return 0.01 * Cauchy(dt); // scaled Cauchy increments
   // return 1.0 * dt + 0.5 * Normal(dt); // Gaussian increments with drift
   // return 20.0 * Poisson(dt) + Normal(dt); // Poisson + normal increments
};

int main() {
   int i;                              // dummy index
   double Tout[N];                     // array with times for output
   double X[N];                        // process realization at discrete times
   ofstream rand_walk_file;            // average number of each specie file
   srand48(time(NULL));                // seed random number generator

// Realize process by stepping through time increments
   double dT = T / (N-1);              // time step between outputs
   Tout[0] = 0.0;
   X[0] = 0.0;
   for (i = 1; i < N; i++) {
      Tout[i] = Tout[i-1] + dT;
      X[i] = X[i-1] + Increment(dT);
   };

// Output random walk realization
   rand_walk_file.open("random_walk.txt");
   for (i = 0; i < N; i++) {
      rand_walk_file << Tout[i] << " "
                     << X[i] << endl;
   };
   rand_walk_file.close();

   return 0; // End of the program
};