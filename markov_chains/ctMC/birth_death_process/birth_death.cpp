// Birth-Death process as a continuous-time Markov chain

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

#define N 100                       // Number of times to discretize realization between 0 and Tf
#define R 10000                     // Number of chain realizations

// Exponential random variable
inline double ExpRand(double rate) {return -log(drand48())/rate;};

// Single step in a birth-death process (Doob-Gillespie algorithm)
double BirthOrDeath(int &population, double birth_rate, double death_rate)
{
// q_{i,i} = -(birth_rate + death_rate), i > 0
   double change_rate = birth_rate + death_rate;
// Find new state. Treat zero (extinct) population as an absorbing state.
   if (population != 0) {
// P_{i,i-1} = -death_rate / q_{i,i}
      if (drand48() < death_rate / change_rate) population -= 1;
// P_{i,i+1} = 1 - P_{i,i-1} = -birth_rate / q_{i,i}
      else population += 1;
   };
// Compute holding time until jump to new state
   return ExpRand(change_rate);
};

int main() {
   int i,j;                            // dummy indices
   int Tlast;                          // index of last output time crossed
   int Tnext;                          // index of next output time crossed
   int X0;                             // initial population
   int Xold;                           // population before jump
   int Xnew;                           // population after jump
   double Rb;                          // number of births per member per unit time
   double Rd;                          // number of deaths per member per unit time
   double Tf;                          // final time to simulate
   double T;                           // current time
   double Tout[N];                     // array with times for output
   double EX[N];                       // expected population over time
   ofstream avg_pop_file;              // average population file
   srand48(time(NULL));                // seed random number generator


// Input simulation parameters
   cout << "Initial population: ";     // Ask for initial population
   cin >> X0;
   cout << "Birth rate: ";             // Ask for birth rate
   cin >> Rb;
   cout << "Death rate: ";             // Ask for death rate
   cin >> Rd;
   cout << "Time to simulate: ";       // Ask for total simulation time
   cin >> Tf;
// Compute times for average
   double dT = Tf / (N-1);             // time step between outputs
   for (i = 0; i < N; i++) {
      Tout[i] = i * dT;
      EX[i] = 0.0;
   };

// Simulate many chains and average results
   for (i = 0; i < R; i++) {
// Reset population
      Tlast = 0;
      T = 0.0;
      Xnew = X0;
      EX[0] += X0;
      while (T < Tf) {
         Xold = Xnew;
// Take step
         T += BirthOrDeath(Xnew, Rb, Rd);
         Tnext = T / dT;
         if (Tnext >= N) Tnext = N-1;
// Update average, if necessary
         for (j = Tlast+1; j <= Tnext; j++) EX[j] += Xold;
         Tlast = Tnext;
      };
   };
// Normalize by number of realizations
   for (i = 0; i < N; i++) EX[i] /= R;

// Output average population
   avg_pop_file.open("population.txt");
   for (i = 0; i < N; i++) avg_pop_file << Tout[i] << " "
                                        << EX[i] << endl;
   avg_pop_file.close();

   return 0; // End of the program
};