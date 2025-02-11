// Law of Large Numbers and Central Limit Theorem
// Random variables available:
// `RV_TYPE` == 0: Bernoulli with success probability `param1`.
// `RV_TYPE` == 1: Uniform in the interval [`param1`, `param2`].
// `RV_TYPE` == 2: Exponential with rate `param1`.
// `RV_TYPE` == 3: Pareto with scale `param1` and shape `param2`.
// `RV_TYPE` == 4: Cauchy with location `param1` and scale `param2`.

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

#define RV_TYPE 0                   // Type of random variable
#define N 10000                     // Number of samples in each i.i.d. sequence
#define R 10000                     // Number of i.i.d. sequence realizations

const double param1 = 0.0;          // Parameter 1 for any distribution
const double param2 = 1.0;          // Parameter 2 for any distribution

// Sample of random variable
inline double Sample()
{
#if RV_TYPE == 0
   return (drand48() < param1 ? 1.0 : 0.0);
#elif RV_TYPE == 1
   return param1 + drand48() * (param2 - param1);
#elif RV_TYPE == 2
   return -log(drand48()) / param1;
#elif RV_TYPE == 3
   return param1 / pow(drand48(), 1.0 / param2);
#elif RV_TYPE == 4
   return param1 + param2 * tan(M_PI * (drand48() - 0.5));
#else
   return 0.0;
#endif
};

// Mean of random variable. Return `is_finite` as false if infinity or undefined.
inline double Mean(bool &is_finite)
{
   is_finite = true;
#if RV_TYPE == 0
   return param1;
#elif RV_TYPE == 1
   return 0.5 * (param1 + param2);
#elif RV_TYPE == 2
   return 1.0 / param1;
#elif RV_TYPE == 3
   if (param2 <= 1.0) is_finite = false;
   return param1 * param2 / (param2 - 1.0);
#elif RV_TYPE == 4
   is_finite = false;
   return 0.0;
#else
   return 0.0;
#endif
};

// Variance of random variable. Return `is_finite` as false if infinity or undefined.
inline double Variance(bool &is_finite)
{
   is_finite = true;
#if RV_TYPE == 0
   return param1 * (1.0 - param1);
#elif RV_TYPE == 1
   return (param2 - param1) * (param2 - param1) / 12.0;
#elif RV_TYPE == 2
   return 1.0 / (param1 * param1);
#elif RV_TYPE == 3
   if (param2 <= 2.0) is_finite = false;
   return param1 * param1 * param2 / ((param2 - 1.0) * (param2 - 1.0) * (param2 - 2.0));
#elif RV_TYPE == 4
   is_finite = false;
   return 1.0;
#else
   return 1.0;
#endif
};

int main() {
   int i,j;                            // dummy indices
   int distro_idx;                     // index for distribution
   double x;                           // dummy variable
   double iid;                         // i.i.d. random variable
   double avg[N];                      // running average of i.i.d. sequence
   double norm_avg;                    // normalized average of one i.i.d. sequence
   double distro[100];                 // distribution of realizations of the normalized average of i.i.d. sequences
   double mean, variance;              // mean and variance of random variable of choice
   double scale;                       // scaling factor for normalized average
   bool is_finite;                     // flag to check for finite/defined mean and variance
   ofstream average_file;              // running averages file
   ofstream distro_file;               // distribution of normalized averages file
   srand48(time(NULL));                // seed random number generator

// Find mean and illustrate LLN if possible
   mean = Mean(is_finite);
   if (is_finite) {
      cout << "The mean of the random variable is " << mean << "." << endl;
// Generate sequence and calculate running sum
      avg[0] = Sample();
      for (i = 1; i < N; i++) {
         iid = Sample();
         avg[i] = avg[i-1] + iid;
      };
// Normalize sum to average and output to file
      average_file.open("average.txt");
      for (i = 0; i < N; i++) average_file << i+1 << " "
                                           << avg[i] / (i+1) << " "
                                           << mean << endl;
      average_file.close();
   }
   else {
      cout << "Mean is infinity or undefined. "
           << "The Law of Large Numbers is not applicable." << endl;
   };

// Find variance and illustrate the CLT if possible
   if (is_finite) variance = Variance(is_finite);

   if (is_finite) {
      cout << "The variance of the random variable is " << variance << "." << endl;
// Generate many realization of i.i.d. sequences and bin normalized averages
      scale = sqrt(N / variance);
      for (j = 0; j < R; j++) {
         norm_avg = 0.0;
         for (i = 0; i < N; i++) norm_avg += Sample();
         norm_avg /= N;
         norm_avg -= mean;
         norm_avg *= scale;
         distro_idx = 10.0 * (5.0 + norm_avg); // Bin between -5 and 5, which should get MOST of the samples
         if (0 <= distro_idx && distro_idx < 100) distro[distro_idx]++;
      };
// Output the distribution of realizations of the normalized average of i.i.d. sequences
      distro_file.open("distro.txt");
      for (i = 0; i < 100; i++) {
         x = -5.0 + i / 10.0;
         distro_file << x << " "
                     << distro[i] * 10.0 / R << " "
                     << exp(-0.5 * x * x) / sqrt(2.0 * M_PI) << endl;
      };
      distro_file.close();
   }
   else {
      cout << "Variance is infinity or undefined. "
           << "The Central Limit Theorem is not applicable." << endl;
   };

   return 0; // End of the program
};