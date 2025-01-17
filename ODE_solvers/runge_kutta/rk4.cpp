// Runge-Kutta (4) method for solving an N dimensional ODE given a "standard" initial condition

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

// ODE as a function of the highest derivative
float ODE(vector<float> &Y, float x)
{
   // Function y'' = -y' - 3y + 0.1*cos(sqrt(3)*x)
   return -Y[1] - 3*Y[0] + 0.1*cos(sqrt(3)*x);
};

// ODE as an size-1 dimensional vector
void nODE(vector<float> &Y, vector<float> &K, float x, float dx, int size)
{
   int i;      // dummy index
   for (i = 0; i < size-1; i++) K[i] = dx*Y[i+1];  // K_i = d^iY/dx^i
   K[size-1] = dx*ODE(Y,x);
};

// Vector-vector addition
void v_add(vector<float> &V1, vector<float> &V2, vector<float> &Vr, int size)
{
   int i;      // dummy index
   for (i = 0; i < size; i++) Vr[i] = V1[i] + V2[i];  // add each component
};

// Vector-scalar multiplication
void vs_mul(float a, vector<float> &V, vector<float> &Vr, int size)
{
   int i;      // dummy index
   for (i = 0; i < size; i++) Vr[i] = a*V[i];         // scale each component
};

int main() {
   // Variable definition
   int i, j;            // dummy indices
   int deg;             // degree of ODE
   int N;               // number of grid points
   float a;             // left endpoint of interval
   float b;             // right endpoint of interval
   float x;             // dummy variable
   float dx;            // step size
   ofstream solution;   // solution file

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
   cout << "Input ODE degree: ";                // Ask for ODE degree
   cin >> deg;
   // Define solution in vector form
   vector<float> sol(deg);
   vector<float> sol_temp(deg);
   // Define RK4 elements in vector form
   vector<float> K1(deg);
   vector<float> K2(deg);
   vector<float> K3(deg);
   vector<float> K4(deg);
   // Ask user for initial values
   for (i = 0; i < deg; i++) {
      cout << "Input initial value " << i << " : ";   // prompt for initial values
      cin >> sol[i];
   };

   // Iterate to solve and record values
   solution.open("solution.txt");               // Open output file
   // Iteration for each grid point
   for (j = 0; j < N; j++) {
      solution << x << " " << sol[0] << endl;   // Output values to file
      // Compute K1
      nODE(sol,K1,x,dx,deg);
      // Compute K2
      vs_mul(0.5,K1,K2,deg);
      v_add(sol,K2,sol_temp,deg);
      nODE(sol_temp,K2,x+dx/2,dx,deg);
      // Compute K3
      vs_mul(0.5,K2,K3,deg);
      v_add(sol,K3,sol_temp,deg);
      nODE(sol_temp,K3,x+dx/2,dx,deg);
      // Compute K4
      v_add(sol,K3,sol_temp,deg);
      nODE(sol_temp,K4,x+dx,dx,deg);
      // Compute solution at new step
      vs_mul(2,K2,K2,deg);
      v_add(K1,K2,K1,deg);
      vs_mul(2,K3,K3,deg);
      v_add(K1,K3,K1,deg);
      v_add(K1,K4,K1,deg);
      vs_mul(1.0/6,K1,K1,deg);      
      v_add(sol,K1,sol,deg);
      x += dx;                //Update grid point
   };
   solution.close();          // Close file

   return 0; // End of the program
};
