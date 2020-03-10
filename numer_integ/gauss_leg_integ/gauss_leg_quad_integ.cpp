// Gaussian quadrature rule of numerical integration for polynomials

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;

// Define function for the function (polynomial) to be integrated
float f(float x)
{
	// Function 1 - x + 3x^2 + (7/2)x^3
	return 1 - x + 3*pow(x,2) + (7/2)*pow(x,3);
}


int main() {
	// Variable definition
	int i, j, k;
	int N, Q;
	float a, b, l, L;
	float pt, wt, S = 0;
	ifstream points, weights;
	string trash;

	// Input basic parameter
	cout << "Input lower bound of integration: "; 	// Ask for lower bound
	cin >> a;
	cout << "Input upper bound of integration: "; 	// Ask for upper bound
	cin >> b;
	l = b - a;					// Compute difference between bounds
	L = a + b;					// Compute sum of bounds
	cout << "Input degree of polynomial: "; 	// Ask for polynomial degree
	cin >> N;
	Q = N / 2 + 1;					// Compute number of terms needed

	// Skip necessary amounts of lines in points and weights files
	// in order to reach the lines with Q many points and weights
	points.open("gauss_leg_quad_pts.txt");		// Open points file
	weights.open("gauss_leg_quad_wts.txt");		// Open weights file
	for(i = 1; i < Q; i++)
	{
		getline(points, trash);
		getline(weights, trash);
	}
	// Read values from Qth line and compute summation
	for(i = 0; i < Q; i++)
	{
		points >> pt;
		weights >> wt;
		S += wt*f(0.5*(l*pt + L));
	}
	S *= 0.5*l;
	points.close();					// Close points file
	weights.close();				// Close weights file

	// Output value
	cout << "Integral = " << S << endl;

	return 0; // End of the program
}