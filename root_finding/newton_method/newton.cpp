// Newton's method for root finding

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;

// Define function for which to find a root
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
	int i, j, k;						// dummy indices
	int N;							// maximum number of interations
	float a, x;						// approximate root, and new guess
	float fa;						// value of function at approximate root
	float tol = 1e-6;					// accuracy tolerance (positive)
	float ntol = -1*tol;					// accuracy tolerance (negative)

	// Input basic parameter
	cout << "Approximate solution: ";			// Ask for initial guess
	cin >> a;

	cout << "Input maximum number of iterations: "; 	// Ask for number of iterations
	cin >> N;

	// Begin iterative process
	for(i = 0; i < N; i++)
	{
		fa = f(a);					// find value of function at approximate root
		if(ntol < fa && fa < tol) {
			break;					// root has been found to desired accuracy
		}
		else {
			x = a - fa/df(a);			// find root of f linearized at a
			a = x;					// Update a --> x
		}
	}

	// Output results
	if(i == N)						// Max number of iterations completed (solution not found)
	{
		cout << "The root could not be approximated to within " << tol << " tolerance in " << N << " iteration(s)." << endl;
		cout << "The current best guess is " << a << " yielding a function value of " << fa << "." << endl;
	}
	else							// solution found
	{
		cout << "The root was approximated to within " << tol << " tolerance in " << i+1 << " iteration(s)." << endl;
		cout << "The root is " << a << " yielding a function value of " << fa << "." << endl;
	}

	return 0; // End of the program
}
