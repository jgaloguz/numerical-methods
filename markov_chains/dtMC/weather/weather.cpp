// Daily weather forecast as a discrete-time, finite state space, time-homogeneous Markov chain

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

const double Psc = 0.1;       // Probability that tomorrow is cloudy given that today is sunny
const double Psr = 0.2;       // Probability that tomorrow is rainy given that today is sunny
const double Pcs = 0.3;       // Probability that tomorrow is sunny given that today is cloudly
const double Pcr = 0.4;       // Probability that tomorrow is rainy given that today is cloudly
const double Prs = 0.1;       // Probability that tomorrow is sunny given that today is rainy
const double Prc = 0.2;       // Probability that tomorrow is cloudy given that today is rainy

// Function to choose next state given current state and transition probabilities
int NextState(int Xn, double P1[3][3])
{
   int Xn1 = 0;                              // next state
   double p = P1[Xn][0];
   double u = drand48();
   while (p < u) p += P1[Xn][++Xn1];
   return Xn1;
};

// Function to multiply Pn and P1
void Multiply(double Pn[3][3], double P1[3][3])
{
   int i,j,k;                                // dummy indices
   double tmp[3][3];                         // temporary matrix for multiplication
   for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
         tmp[i][j] = 0.0;
         for (k = 0; k < 3; k++) tmp[i][j] += Pn[i][k] * P1[k][j];
      };
   };
   for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) Pn[i][j] = tmp[i][j];
   };
};

int main() {
   int n, i, j;                              // dummy indices
   int N;                                    // number of days to forecast
   int Xn;                                   // today's weather
   double P1[3][3];                          // 1-step transition matrix
   double Pn[3][3];                          // n-step transition matrix
   double L[3] = {0.0};                      // estimate of the limiting distribution
   srand48(time(NULL));                      // seed random number generator
   ofstream forecast_file;                   // forecast file

// Get user input
   cout << "Input maximum number of days to forecast: ";    // Ask for number of days to forecast
   cin >> N;
   cout << "Input today's weather"
        << " (0 for sunny, 1 for cloudy, 2 for rainy): ";   // Ask for today's weather
   cin >> Xn;

// Assemble 1-step transition probabilities
   P1[0][0] = 1.0 - Psc - Psr;
   P1[0][1] = Psc;
   P1[0][2] = Psr;
   P1[1][0] = Pcs;
   P1[1][1] = 1.0 - Pcs - Pcr;
   P1[1][2] = Pcr;
   P1[2][0] = Prs;
   P1[2][1] = Prc;
   P1[2][2] = 1.0 - Prs - Prc;
   for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) Pn[i][j] = P1[i][j];
   };

// Loop over days
   forecast_file.open("forecast.dat");
   L[Xn] += 1.0;
   forecast_file << Xn << endl;
   for (n = 0; n < N; n++) {
      Xn = NextState(Xn, P1);
      L[Xn] += 1.0;
      forecast_file << Xn << endl;
      Multiply(Pn,P1);
   };
   forecast_file.close();

// Print estimates of limiting distributions
   cout << "Limiting distribution from samples: " << endl;
   for (i = 0; i < 3; i++) cout << setw(12) << L[i] / (double)N;
   cout << endl;
   cout << "Limiting distribution from N-step transition probabilities: " << endl;
   for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) cout << setw(12) << Pn[i][j];
      cout << endl;
   };
   cout << endl;
  
   return 0; // End of the program
};
