// Solution to Lorenz (atmospheric convection) model showing the butterfly effect utilizing RK4

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;

// Lorentz system
void lorenz(vector<float> &X, vector<float> &V, float sigma, float rho, float beta)
{
   // dx/dt = sigma*(y - x)
   V[0] = sigma*(X[1] - X[0]);
   // dy/dt = x*(rho - z) - y
   V[1] = X[0]*(rho - X[2]) - X[1];
   // dz/dt = x*y - beta*z
   V[2] = X[0]*X[1] - beta*X[2];
};

// Vector-vector addition
void v_add(vector<float> &V1, vector<float> &V2, vector<float> &Vr, int size)
{
   int i;
   for (i = 0; i < size; i++) Vr[i] = V1[i] + V2[i];  // add components
};

// Vector-scalar multiplication
void vs_mul(float a, vector<float> &V, vector<float> &Vr, int size)
{
   int i;
   for (i = 0; i < size; i++) Vr[i] = a*V[i];      // scale components
};

int main() {
   // Variable definition
   int i, j;         // dummy indices
   int N = 10000;       // number of iterations
   float sigma = 10, rho = 28, beta = 8.0/3; // parameters
   float x0 = 1, y0 = 1, z0 = 1; // Initial conditions
   float t = 0, dt = 0.01;    // Initial time and step size
   ofstream solution;      // Output file

   // Define trajectory and derivative in vector form
   vector<float> X(3);
   vector<float> V(3);
   // Define RK4 elements in vector form
   vector<float> K1(3);
   vector<float> K2(3);
   vector<float> K3(3);
   vector<float> K4(3);

   // Set initial condition
   X[0] = x0;
   X[1] = y0;
   X[2] = z0;

   // Iterate to solve and record values
   solution.open("butterfly.txt");        // Open output file
   for (j = 0; j < N; j++) {              // Iteration for each grid point
      solution << X[0] << " " << X[1] << " " << X[2] << " " << t << " " << endl; // Output values to file
      // Compute K1
      lorenz(X, K1, sigma, rho, beta);
      vs_mul(dt,K1,K1,3);
      // Compute K2
      vs_mul(0.5,K1,K2,3);
      v_add(X,K2,V,3);
      lorenz(V, K2, sigma, rho, beta);
      vs_mul(dt,K2,K2,3);
      // Compute K3
      vs_mul(0.5,K2,K3,3);
      v_add(X,K3,V,3);
      lorenz(V, K3, sigma, rho, beta);
      vs_mul(dt,K3,K3,3);
      // Compute K4
      v_add(X,K3,V,3);
      lorenz(V, K4, sigma, rho, beta);
      vs_mul(dt,K4,K4,3);
      // Compute solution at new step
      vs_mul(2,K2,K2,3);
      v_add(K1,K2,K1,3);
      vs_mul(2,K3,K3,3);
      v_add(K1,K3,K1,3);
      v_add(K1,K4,K1,3);
      vs_mul(1.0/6,K1,K1,3);     
      v_add(X,K1,X,3);
      t += dt;                //Update grid point
   };
   solution.close();          // Close file

   return 0; // End of the program
};
