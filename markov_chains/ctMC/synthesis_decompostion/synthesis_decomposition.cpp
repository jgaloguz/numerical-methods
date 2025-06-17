// Synthesis-Decomposition reaction as a continuous-time Markov chain

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

#define N 100                       // Number of times to discretize realization between 0 and Tf
#define R 10000                     // Number of chain realizations

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

// Simulate reactions in a set amount of time (tau-leaping algorithm)
void Reactions(int *species, double synthesis_rate, double decomposition_rate)
{
// Find the net change from synthesis and decomposition, and apply it to the species
   int net_change = PoiRand(synthesis_rate) - PoiRand(decomposition_rate);
   species[0] -= net_change;
   species[1] -= net_change;
   species[2] += net_change;
// If limiting reagent is negative (i.e. ran out), adjust species counts accordingly
   int lim_reag = fmin(species[0], species[1]);
   if (lim_reag < 0) {
      species[0] -= lim_reag;
      species[1] -= lim_reag;
      species[2] += lim_reag;
   }
// If instead the product is negative (i.e. ran out), adjust species counts accordingly
   else if (species[2] < 0) {
      species[0] += species[2];
      species[1] += species[2];
      species[2] = 0;
   };
// Note that they won't both be negative simultaneously because their net change is opposite
};

int main() {
   int i,j,k;                          // dummy indices
   int A0, B0, C0;                     // initial number of each specie
   int Xold[3];                        // population before jump
   int Xnew[3];                        // population after jump
   double Rs;                          // Synthesis rate
   double Rd;                          // Decomposition rate
   double Tf;                          // final time to simulate
   double Tout[N];                     // array with times for output
   double EX[N][3];                    // expected number of each specie over time
   ofstream avg_num_file;              // average number of each specie file
   srand48(time(NULL));                // seed random number generator


// Input simulation parameters
   cout << "Initial population of A: ";      // Ask for initial population of A
   cin >> A0;
   cout << "Initial population of B: ";      // Ask for initial population of B
   cin >> B0;
   cout << "Initial population of C: ";      // Ask for initial population of C
   cin >> C0;
   cout << "Synthesis rate: ";               // Ask for synthesis rate
   cin >> Rs;
   cout << "Decomposition rate: ";           // Ask for decomposition rate
   cin >> Rd;
   cout << "Time to simulate: ";             // Ask for total simulation time
   cin >> Tf;
// Compute times for average
   double dT = Tf / (N-1);                   // time step between outputs
   for (i = 0; i < N; i++) {
      Tout[i] = i * dT;
      for (j = 0; j < 3; j++) EX[i][j] = 0.0;
   };

// Simulate many chains and average results
   for (k = 0; k < R; k++) {
      cout << "\rTrial: " << k+1;
// Reset population
      Xnew[0] = A0;
      Xnew[1] = B0;
      Xnew[2] = C0;
      for (j = 0; j < 3; j++) EX[0][j] += Xnew[j];
      for (i = 1; i < N; i++) {
         for (j = 0; j < 3; j++) Xold[j] = Xnew[j];
// Update species
         Reactions(Xnew, Xold[0]*Xold[1]*Rs*dT, Xold[2]*Rd*dT);
// Update average
         for (j = 0; j < 3; j++) EX[i][j] += Xnew[j];
      };
   };
   cout << endl;
// Normalize by number of realizations
   for (i = 0; i < N; i++) {
      for (j = 0; j < 3; j++) EX[i][j] /= R;
   };

// Output average reaction
   avg_num_file.open("reaction.txt");
   for (i = 0; i < N; i++) {
      avg_num_file << Tout[i] << " ";
      for (j = 0; j < 3; j++) avg_num_file << EX[i][j] << " ";
      avg_num_file << endl;
   };
   avg_num_file.close();

   return 0; // End of the program
};
