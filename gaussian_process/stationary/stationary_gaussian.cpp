// Simulate a Gaussian process given its mean and covariance function

#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

constexpr double M_2PI = 2.0 * M_PI;

// Square function
inline double Sqr(double x) {return x*x;};

// Generate two independent normally distributed random numbers using the Box-Muller method
void BoxMuller(double &N1, double &N2)
{
   double U1 = drand48();
   double U2 = drand48();
   N1 = sqrt(-2.0 * log(U1)) * cos(M_2PI * U2);
   N1 = sqrt(-2.0 * log(U1)) * sin(M_2PI * U2);
};

// Forward discrete Fourier transport with symmetric time and frequency ranges
void FDFT(double *dct, double *dst, double *k, double *signal, double *t, int N)
{
   int j, n;                  // dummy indices

// Loop in frequency
   for(n = 0; n < N; n++) {
      dct[n] = dst[n] = 0.0;
// Loop in time
      for(j = 0; j < N; j++) {
         dct[n] += signal[j] * cos(t[j] * k[n]);   // real part
         dst[n] -= signal[j] * sin(t[j] * k[n]);   // imaginary part
      };
   };
};

// Covariance function of gaussian process.
inline double Cov(double t)
{
   // return exp(-fabs(t));                  // Abel kernel (Ornstein-Uhlenbeck)
   return exp(-0.5 * Sqr(t));             // Gaussian kernel
};

int main(void) {
   int j, n;                           // dummy indices
   int N;                              // number of time points
   double L;                           // final time to simulate
   double dt;                          // time step
   double dk;                          // frequency step
   double mag, ang;                    // magnitude and phase angle of complex number
   double g;                           // temporary holder for a normally distributed variable in the iid sequence
   double tjkn;                        // product of time and frequency
   double X, Y;                        // independent realizations of stationary Gaussian processes
   double *t;                          // time array
   double *k;                          // frequency array
   double *Ct;                         // covariance vector in time
   double *Ckr;                        // covariance vector in frequency (real part)
   double *Cki;                        // covariance vector in frequency (imaginary part)
   double *gr, *gi;                    // iid sequences of normally distributed random variables
   ofstream process_file;              // output file
   srand48(time(NULL));                // seed random number generator

// Input simulation parameters
   cout << "Time to simulate: ";       // Ask for total simulation time
   cin >> L;
   cout << "Number of points: ";       // Ask for number of time points
   cin >> N;

// Allocate memory
   t = new double[N];
   k = new double[N];
   Ct = new double[N];
   Ckr = new double[N];
   Cki = new double[N];
   gr = new double[N];
   gi = new double[N];

// Load time, frequency, covariance function, and iid sequences arrays
// NOTE: Time is shifted by L / 2 to avoid numerical problems when C(t) is not periodic in [0,L].
//       Frequency is shifted by dk * N / 2 in case C(t) is derived from C(k) with a backward DFT.
//       Recall that C(k) must be symmetric because C(t) is real-valued, hence the frequency shift.
   dt = L / N;
   dk = M_2PI / L;
   for (j = 0; j < N; j++) {
      t[j] = j * dt - 0.5 * L;
      k[j] = dk * (j - 0.5 * N);
      Ct[j] = Cov(t[j]);
      BoxMuller(gr[j], gi[j]);
   };

// Find unnormalized DFT of covariance vector
   FDFT(Ckr, Cki, k, Ct, t, N);
// Normalize DFT, take square root, and multiply by (gr + i * gi)
// NOTE: The normalization of the DFT process is dt = L / N.
//       The square root taken is of DFT * dk / twopi = DFT / L.
//       Therefore, the net normalization before the root is 1 / N.
// NOTE: (a_r + i * a_i) * (b_r + i * b_i) = (a_r * b_r - a_i * b_i) + i * (a_i * b_r + a_r * b_i)
   for (j = 0; j < N; j++) {
      Ckr[j] /= N;
      Cki[j] /= N;
      mag = sqrt(Sqr(Ckr[j]) + Sqr(Cki[j]));
      ang = atan2(Cki[j], Ckr[j]);
      Ckr[j] = sqrt(mag) * cos(0.5 * ang);
      Cki[j] = sqrt(mag) * sin(0.5 * ang);
      g = gr[j];
      gr[j] = Ckr[j] * g - Cki[j] * gi[j];
      gi[j] = Cki[j] * g + Ckr[j] * gi[j];
   };

// Simulate process
   process_file.open("stationary_gaussian.txt");
   process_file << std::setprecision(8);
   for (j = 0; j < N; j++) {
      X = 0.0;
      Y = 0.0;
      for (n = 0; n < N; n++) {
         tjkn = t[j] * k[n];
         X += gr[n] * cos(tjkn) - gi[n] * sin(tjkn);
         Y += gi[n] * cos(tjkn) + gr[n] * sin(tjkn);
      };
      process_file << setw(16) << t[j]
                   << setw(16) << X
                   << setw(16) << Y
                   << std::endl;
   };
   process_file.close();

// Clean-up
   delete[] t;
   delete[] k;
   delete[] Ct;
   delete[] Ckr;
   delete[] Cki;
   delete[] gr;
   delete[] gi;

   return 0;         // end of program
};