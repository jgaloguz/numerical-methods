// Euler's method for solving an N dimensional ODE given a "standard" initial condition

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;

// Define function for the ODE
float ODE(vector<float> &Y, float x)
{
	// Function y'' = -y' - 3y + 0.1*cos(sqrt(3)*x)
	return -Y[1]-3*Y[0] + 0.1*cos(sqrt(3)*x);
}

// Define function for factorial
int fact(int n)
{
	if (n == 0)
	{
		return 1;
	}
	else
	{
		return n*fact(n-1);
	}
}

int main() {
	// Variable definition
	int i, j, k;
	int deg, N;
	float a, b, x, dx;
	ofstream solution;

	// Input grid parameters
	cout << "Input initial value location: "; 	// Ask for initial value location
	cin >> a;
	x = a;						// Set initial grid point to a
	cout << "Input final value location: "; 	// Ask for final value location
	cin >> b;
	cout << "Input number of grid points: "; 	// Ask for number of grid points
	cin >> N;
	dx = (b-a)/(N-1);				// Compute step size

	// Input initial values
	cout << "Input ODE degree: ";			// Ask for ODE degree
	cin >> deg;
	vector<float> sol(deg+1);			// Define vector to hold solution and
							// derivatives at each point in grid
	for(i = 0; i < deg; i++)			// Ask user for initial values
	{
		cout << "Input initial value " << i << " : ";
		cin >> sol[i];
	}

	// Iterate to solve and record values
	solution.open("solution.txt");			// Open output file
	for(k = 0; k < N; k++)				// Iteration for each grid point
	{
		sol[deg] = ODE(sol,x);			// Find highest derivative from initial
							// values from the ODE equation
		solution << x << " " << sol[0] << endl; // Output values to file
		x += dx;				// Update grid point
		for(i = 0; i < deg; i++)		// Iteration for each derivative
		{
			for(j = i+1; j <= deg; j++)	// Taylor's approximation
			{
				sol[i] += (sol[j]/fact(j-i))*pow(dx,(j-i));
			}
		}
	}
	solution.close();				// Close file
	return 0; // End of the program
}
