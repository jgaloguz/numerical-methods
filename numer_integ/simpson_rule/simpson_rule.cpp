// Simpson's Rule for approximating definite integrals

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;

// Define function for the function to be integrated
float f(float x)
{
	// Function 1 - x + 3x^2 + (7/2)x^3
	return 1 - x + 3*pow(x,2) + 3.5*pow(x,3);
}

int main() {
	// Variable definition
	int i, j, k;					// dummy indices
	int N, M;					// number of grid points and intervals
	float a, b;					// endpoints of interval
	float dx, x;					// step size and current location
	float S = 0;					// result

	// Input basic parameter
	cout << "Input lower bound of integration: "; 	// Ask for lower bound
	cin >> a;
	x = a;						// Set initial point at a
	cout << "Input upper bound of integration: "; 	// Ask for upper bound
	cin >> b;
	cout << "Input number of grid points: "; 	// Ask for number of grid points
	cin >> N;
	M = N-1;					// Compute number of intervals
	dx = (b - a)/M;					// Compute step size

	// Approximate solution
	for(i = 1; i < M; i++)
	{
		x += dx;				// take step
		S += (i % 2 ? 4.0/3 : 2.0/3) * f(x);	// add 4/3 * f(x) if odd
	}						//  or 2/3 * f(x) if even
	S += (f(a) + f(b))/3;				// add endpoint terms
	S *= dx;					// scale by step size

	// Output value
	cout << "Integral = " << S << endl;

	return 0; // End of the program
}
