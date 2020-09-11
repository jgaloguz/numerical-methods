// Newton's method for root finding

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;

// Define function
float f(float x)
{
	// Function 2 - e^x
	return 2 - exp(x);
}

// Define derivative of the function
float df(float x)
{
	// Function - e^x
	return -exp(x);
}

int main() {
	// Variable definition
	int i, j, k, N;
	float a, x, fa;
	float tol = 1e-6;
	float ntol = -1*tol;

	// Input basic parameter
	cout << "Approximate solution: ";					// Ask for initial guess
	cin >> a;

	cout << "Input maximum number of iterations: "; 	// Ask for number of iterations
	cin >> N;

	// Begin iterative process
	for(i = 0; i < N; i++)
	{
		fa = f(a);
		if(ntol < fa && fa < tol) {
			break;
		}
		else {
			x = a - fa/df(a);
			a = x;					// Update a --> x
		}
	}

	// Output results
	if(i == N)						// Max number of iterations completed
	{
		cout << "The root could not be approximated to within " << tol << " tolerance in " << N << " iteration(s)." << endl;
		cout << "The current best guess is " << a << " yielding a function value of " << fa << "." << endl;
	}
	else
	{
		cout << "The root was approximated to within " << tol << " tolerance in " << i+1 << " iteration(s)." << endl;
		cout << "The root is " << a << " yielding a function value of " << fa << "." << endl;
	}

	return 0; // End of the program
}