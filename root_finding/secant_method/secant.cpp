// Secant method for root finding

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;

// Define function for the function (polynomial) to be integrated
float f(float x)
{
	// Function 2 - e^x
	return 2 - exp(x);
}


int main() {
	// Variable definition
	int i, j, k, N;
	float a, b, c, R;
	float fa,fb,fc;
	float tol = 1e-6;
	float ntol = -1*tol;

	// Input basic parameter
	cout << "Input left bound for interval: ";		// Ask for left bound of interval
	cin >> a;
	cout << "Input right bound for interval: ";		// Ask for right bound of interval
	cin >> b;
	
	// Make sure there is at least one solution in the given interval
	fa = f(a);
	fb = f(b);
	if(fa*fb > 0)
	{
		cout << "Both end points for the given interval have the same sign." << endl;
		cout << "Cannot guarantee root exists within the given interval." << endl;
		cout << "Please provide endpoints with opposite signs." << endl;
		return 0;
	}

	cout << "Input maximum number of iterations: "; 	// Ask for number of iterations
	cin >> N;

	// Begin iterative process
	for(i = 0; i < N; i++)
	{
		c = (a*fb - b*fa)/(fb - fa);
		fc = f(c);
		if(ntol < fc && fc < tol)
		{
			break;					// Solution found within specified tolerance
		}
		else
		{
			a = b;					// Update a --> b
			fa = fb;
			b = c;					// Update b --> c
			fb = fc;
		}
	}

	// Output results
	if(i == N)						// Max number of iterations completed
	{
		cout << "The root could not be approximated to within " << tol << " tolerance in " << N << " iteration(s)." << endl;
		cout << "The current best guess is " << c << " yielding a function value of " << fc << "." << endl;
	}
	else
	{
		cout << "The root was approximated to within " << tol << " tolerance in " << i+1 << " iteration(s)." << endl;
		cout << "The root is " << c << " yielding a function value of " << fc << "." << endl;
	}

	return 0; // End of the program
}
