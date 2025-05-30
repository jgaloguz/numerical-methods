// MCMC applied to the problem of 2D Ising-lattice magnetization

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

#define N 100        // Length of either side of 2D lattice

// Function for computing the total, signed magnetization of a lattice
long TotalSignedMagnetization(double lattice[N][N])
{
   int i,j;          // dummy indices
   long M = 0;       // average magnetization
   for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
         M += (long)lattice[i][j];
      };
   };
   return M;
};

// Function to evolve the Markov Chain based on the Metropolis-Hastings algorithm
void MarkovChain(double lattice[N][N], double T, long &tsM)
{
   int i = drand48() * N;        // row of cell of Ising-lattice to flip
   int j = drand48() * N;        // column of cell of Ising-lattice to flip

   int i_pls = (i+1) % N;        // row of right neighbor cell
   int i_mns = (i-1) % N;        // row of left neighbor cell
   int j_pls = (j+1) % N;        // row of top neighbor cell
   int j_mns = (j-1) % N;        // row of bottom neighbor cell

   double H_ij = lattice[i][j] * ( lattice[i_pls][j] + lattice[i_mns][j]
                                 + lattice[i][j_pls] + lattice[i][j_mns]); // local binding energy

// NOTE: if H = {(positive) sum over product of neighboring spins}, then
// pi_j / pi_i = exp[(H(j)-H(i))/T] for current state i and proposed state j.
// Since the proposed state is just a single spin flip, then
// H(j)-H(i) = -2.0 * {local energy of current spin}, prior to flip
   double acc_prob = fmin(1.0, exp(-2.0 * H_ij / T)); // acceptance probability (Metropolis-Hastings)

   if (drand48() < acc_prob) {               // if proposed state is accepted
      lattice[i][j] *= -1.0;                 // flip spin
      tsM += 2 * (long)lattice[i][j];        // {new tsM} = {old tSM} + 2 * {new spin state}
   };
};

int main() {
   double lattice[N][N];                     // 2D Ising-lattice
   double M;                                 // Average (unsigned) magnetization
   long tuM;                                 // Total unsigned magnetization
   long tsM;                                 // Total signed magnetization
   double T;                                 // Temperature
   double T_low = 0.1;                       // Lowest temperature to search
   double T_high = 5.0;                      // Highest temperature to search
   double N_T = 100;                         // Number of temperatures to try
   double dT = (T_high - T_low) / (N_T-1);   // Temperature increment
   long burn_in_time = 10 * N * N;           // Burn-in time
   long MC_trials = 100 * N * N;             // Number of MC samples from stationary distribution
   long i,j;                                 // dummy indices
   srand48(time(NULL));                      // seed random number generator
   ofstream solution_file;                   // solution file

// Initial condition (uniform), technically the most likely configuration at ANY temperature
   for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
         lattice[i][j] = 1.0;
      };
   };
   tsM = TotalSignedMagnetization(lattice);     // Initialize total, signed magnetization

   solution_file.open("M_vs_T.dat");            // Open output file
// Loop over temperatures
   T = T_low;
   for (i = 0; i < N_T; i++) {
      cout << T << endl;
// Evolve chain for the burn-in time
      for (j = 0; j < burn_in_time; j++) MarkovChain(lattice, T, tsM);
// Find average magnetization using Monte Carlo method
      tuM = 0;
      for (j = 0; j < MC_trials; j++) {
         MarkovChain(lattice, T, tsM);
         tuM += (tsM > 0 ? tsM : -tsM);
      };
      M = (double)tuM / (double)(N * N * MC_trials);  // Normalize to make it an average
      solution_file << T << " " << M << endl;   // Output values to file
      T += dT;
   };
   solution_file.close();                       // Close output file
   
   return 0; // End of the program
};
