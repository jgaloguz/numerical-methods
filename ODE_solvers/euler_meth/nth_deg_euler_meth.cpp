// Euler's method for solving an N dimensional ODE given a "standard" initial condition

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

// ODE as a function of the highest derivative
float ODE(vector<float> &Y, float x)
{
   // Function y'' = -y' - 3y + 0.1*cos(sqrt(3)*x)
   return -Y[1]-3*Y[0] + 0.1*cos(sqrt(3)*x);
};

// Factorial (recursively defined)
int fact(int n)
{
   if (n == 0) return 1;      // End of recursion
   else return n*fact(n-1);   // Return n * factorial of n - 1 (recursive call)
};

int main() {
   // Variable definition
   int i, j, k;         // dummy indices
   int deg;       // degree of ODE
   int N;            // number of grid points
   float a;       // left endpoint of interval
   float b;       // right endpoint of interval
   float x;       // dummy variable
   float dx;         // step size
   ofstream solution;      // solution file

   // Input grid parameters
   cout << "Input initial value location: ";    // Ask for initial value location
   cin >> a;
   x = a;                                       // Set initial grid point to a
   cout << "Input final value location: ";      // Ask for final value location
   cin >> b;
   cout << "Input number of grid points: ";     // Ask for number of grid points
   cin >> N;
   dx = (b-a)/(N-1);                            // Compute step size

   // Input initial values
   cout << "Input ODE degree: ";       // Ask for ODE degree
   cin >> deg;
   vector<float> sol(deg+1);           // Define vector to hold solution and derivatives at each point in grid
   // Ask user for initial values
   for (i = 0; i < deg; i++) {
      cout << "Input initial value " << i << " : ";   // prompt for initial values
      cin >> sol[i];
   };

   // Iterate to solve and record values
   solution.open("solution.txt");               // Open output file
   // Iteration for each grid point
   for (k = 0; k < N; k++) {
      sol[deg] = ODE(sol,x);                    // Find highest derivative from initial values from the ODE equation
      solution << x << " " << sol[0] << endl;   // Output values to file
      x += dx;                                  // Update grid point
      // Iteration for each derivative
      for (i = 0; i < deg; i++) {
         for (j = i+1; j <= deg; j++) {
            sol[i] += (sol[j]/fact(j-i))*pow(dx,(j-i));  // Taylor's approximation
         };
      };
   };
   solution.close();          // Close file

   return 0; // End of the program
};
