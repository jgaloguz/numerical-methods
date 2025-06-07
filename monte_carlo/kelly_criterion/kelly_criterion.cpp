// Monte Carlo method to verify the Kelly criterion

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

#define N 1000                               // number of bets per trial
#define M 1000                               // number of MC trials

const double p = 0.8;                        // probability of winning
const double g = 1.0;                        // fraction gained with win
const double l = 1.0;                        // fraction lost with loss

// Function to generate Bernouilli random number
inline int Bern() {return (drand48() < p ? 1 : 0);};

int main() {
   int i, j, k;                              // dummy indices
   int Nf = 50;                              // number of betting fractions to test
   double money;                             // log wealth in a single set of bets
   double wealth[Nf];                        // average log wealth
   double frac[Nf];                          // fraction of wealth to bet
   srand48(time(NULL));                      // seed random number generator
   ofstream wealth_file;                     // wealth file

// Initialize wealth and betting fraction arrays
   for (i = 0; i < Nf; i++) {
      wealth[i] = 0.0;
      frac[i] = (double)i / (double)(Nf-1);
   };

// Loop over realizations
   for (j = 0; j < M; j++) {
// Loop over wealth fractions
      for (k = 0; k < Nf; k++) {
         money = 0.0;
// Loop over bets
         for (i = 0; i < N; i++) {
            if (Bern()) money += log(1.0 + g * frac[k]);
            else money += log(1.0 - l * frac[k]);
         };
         wealth[k] += money;
      };
   };
// Normalize wealth
   for (i = 0; i < Nf; i++) wealth[i] = wealth[i] / M;

// Output theoretical and simulation wealth
   wealth_file.open("wealth.txt");
   for (i = 0; i < Nf; i++) {
      wealth_file << setw(12) << frac[i]
                  << setw(12) << wealth[i]
                  << endl;
   };
   wealth_file.close();
  
   return 0; // End of the program
};
