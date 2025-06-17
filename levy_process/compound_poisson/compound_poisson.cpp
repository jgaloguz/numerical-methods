// Synthesis-Decomposition reaction as a continuous-time Markov chain

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

#define R 2.0                       // Jump ate of compound Poisson process
#define T 10.0                      // Final time to simulate
#define N 1000                      // Number of times to discretize realization between 0 and T

// Exponential random variable
inline double Expon(double rate) {return -log(drand48())/rate;};

// Jump according to some jump size distribution
double Jump(double &x)
{
   x += drand48(); // uniform[0,1], E[JumpSize] = 0.5
   return Expon(R); // output wait time until jump
};

int main() {
   int i,j;                            // dummy indices
   int Tlast;                          // index of last output time crossed
   int Tnext;                          // index of next output time crossed
   double Tnow;                        // current time
   double Xold;                        // population before jump
   double Xnew;                        // population after jump
   double Tout[N];                     // array with times for output
   double X[N];                        // process realization at discrete times
   ofstream rand_walk_file;            // average number of each specie file
   srand48(time(NULL));                // seed random number generator

// Compute times for output
   double dT = T / (N-1);              // time step between outputs
   Tout[0] = 0.0;
   for (i = 1; i < N; i++) Tout[i] = Tout[i-1] + dT;

// Realize process by stepping throug jumps
   Tlast = 0;
   Tnow = 0.0;
   X[0] = 0.0;
   Xnew = X[0];
   while (Tnow < T) {
      Xold = Xnew;
// Take step
      Tnow += Jump(Xnew);
      Tnext = Tnow / dT;
      if (Tnext >= N) Tnext = N-1;
// Update realization, if necessary
      for (j = Tlast+1; j <= Tnext; j++) X[j] = Xold;
      Tlast = Tnext;
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