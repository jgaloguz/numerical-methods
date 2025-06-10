// Predator-prey model as a continuous-time Markov chain

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <chrono>

using namespace std;

#define METHOD 1                    // Which method to use (0: Doob-Gillespie; 1: tau-leaping)
#define N 3000                      // Number of times to discretize realization between 0 and Tf
#define R 10000                     // Number of chain realizations

// Exponential random variable
inline double ExpRand(double rate) {return -log(drand48())/rate;};

// Poisson random variable
inline int PoiRand(double rate) {
   double U = drand48();
   int k = 0;
   double e_rate = exp(-rate);
   double term = 1.0, CDF = 1.0;
   while (U > CDF * e_rate) {
      k++;
      term *= rate / k;
      CDF += term;
   };
   return k;
};

// Simulate the next interaction only (Doob-Gillespie algorithm)
double DoobGill(int *populations, double Rhb, double Rhd, double Rlb, double Rld)
{
// total rate
   double change_rate = Rhb + Rhd + Rlb + Rld;
   double u = drand48();
// Find new state.
   if (u < Rhb / change_rate) populations[0] += 1;
   else if (u < (Rhb + Rhd) / change_rate) populations[0] -= 1;
   else if (u < (Rhb + Rhd + Rlb) / change_rate) populations[1] += 1;
   else populations[1] -= 1;

// If either population goes extinct, revive it
   if (populations[0] <= 0) populations[0] = 1;
   if (populations[1] <= 0) populations[1] = 1;

// Compute holding time until jump to new state
   return ExpRand(change_rate);
};

// Simulate interactions in a set amount of time (tau-leaping algorithm)
void Tauleap(int *populations, double Rhb_dt, double Rhd_dt, double Rlb_dt, double Rld_dt)
{
// Find the net change from births and deaths, and apply it to the populations
   populations[0] += PoiRand(Rhb_dt) - PoiRand(Rhd_dt);
   populations[1] += PoiRand(Rlb_dt) - PoiRand(Rld_dt);

// If either population goes extinct, revive it
   if (populations[0] <= 0) populations[0] = 1;
   if (populations[1] <= 0) populations[1] = 1;
};

int main() {
   int i,j,k;                          // dummy indices
   int Tlast;                          // index of last output time crossed
   int Tnext;                          // index of next output time crossed
   int H0, L0;                         // initial number of each population
   int Xold[2];                        // population before jump
   int Xnew[2];                        // population after jump
   double Rhb;                         // prey natural birth-rate
   double Rhd;                         // prey hunt-induced death-rate
   double Rlb;                         // predator hunt-induced birth-rate
   double Rld;                         // predator natural death-rate
   double Tf;                          // final time to simulate
   double T;                           // current time
   double Tout[N];                     // array with times for output
   double EX[N][2];                    // expected number of each specie over time
   ofstream avg_pop_file;              // average number of each specie file
   srand48(time(NULL));                // seed random number generator


// Input simulation parameters
   cout << "Initial prey population: ";            // Ask for initial population of prey
   cin >> H0;
   cout << "Initial predator population: ";        // Ask for initial population of predators
   cin >> L0;
   cout << "Prey natural birth-rate: ";            // Ask for prey natural birth-rate
   cin >> Rhb;
   cout << "Prey hunt-induced death-rate: ";       // Ask for prey hunt-induced death-rate
   cin >> Rhd;
   cout << "Predator hunt-induced birth-rate: ";   // Ask for predator hunt-induced birth-rate
   cin >> Rlb;
   cout << "Predator natural death-rate: ";        // Ask for predator natural death-rate
   cin >> Rld;
   cout << "Time to simulate: ";                   // Ask for total simulation time
   cin >> Tf;

// Compute times for average
   double dT = Tf / (N-1);                         // time step between outputs
   for (i = 0; i < N; i++) {
      Tout[i] = i * dT;
      for (j = 0; j < 2; j++) EX[i][j] = 0.0;
   };

// Simulate many chains and average results
   auto start = chrono::high_resolution_clock::now();
   for (k = 0; k < R; k++) {
      cout << "\rTrial: " << k+1;
// Reset population
      Xnew[0] = H0;
      Xnew[1] = L0;
      for (j = 0; j < 2; j++) EX[0][j] += Xnew[j];
// Iterate through time with choice of method
#if METHOD == 0
      Tlast = 0;
      T = 0.0;
      while (T < Tf) {
         for (j = 0; j < 2; j++) Xold[j] = Xnew[j];
// Update population
         T += DoobGill(Xnew, Xold[0]*Rhb, Xold[0]*Xold[1]*Rhd, Xold[0]*Xold[1]*Rlb, Xold[1]*Rld);
         Tnext = T / dT;
         if (Tnext >= N) Tnext = N-1;
// Update average, if necessary
         for (i = Tlast+1; i <= Tnext; i++) {
            for (j = 0; j < 2; j++) EX[i][j] += Xold[j];
         };
         Tlast = Tnext;
      };
#else
      for (i = 1; i < N; i++) {
         for (j = 0; j < 2; j++) Xold[j] = Xnew[j];
// Update population
         Tauleap(Xnew, Xold[0]*Rhb*dT, Xold[0]*Xold[1]*Rhd*dT, Xold[0]*Xold[1]*Rlb*dT, Xold[1]*Rld*dT);
// Update average
         for (j = 0; j < 2; j++) EX[i][j] += Xnew[j];
      };
#endif
   };
   auto end = chrono::high_resolution_clock::now();
   cout << endl;
// Normalize by number of realizations
   for (i = 0; i < N; i++) {
      for (j = 0; j < 2; j++) EX[i][j] /= R;
   };

// Output average population
   avg_pop_file.open("population.txt");
   for (i = 0; i < N; i++) {
      avg_pop_file << Tout[i] << " ";
      for (j = 0; j < 2; j++) avg_pop_file << EX[i][j] << " ";
      avg_pop_file << endl;
   };
   avg_pop_file.close();

// Output time
   cout << "time = " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;

   return 0; // End of the program
};