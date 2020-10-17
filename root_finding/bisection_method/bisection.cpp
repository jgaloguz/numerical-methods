// Bisection method for root finding

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;

// Define function for which to find root
float f(float x)
{
	// Function 2 - e^x
	return 2 - exp(x);
}


int main() {
	// Variable definition
	int i, j, k;						// dummy indices
	int N;							// maximum number of iterations
	float a, b, c;						// left, right, and mid-points of (sub)intervals
	float fc;						// value of function at midpoint
	float tol = 1e-6;					// accuracy tolerance (positive)
	float ntol = -1*tol;					// accuracy tolerance (negative)

	// Input basic parameter
	cout << "Input left bound for interval: ";		// Ask for left bound of interval
	cin >> a;
	cout << "Input right bound for interval: ";		// Ask for right bound of interval
	cin >> b;
	
	// Make sure there is at least one solution in the given interval
	if(f(a)*f(b) > 0)
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
		c = (a + b)/2;					// find mid point of interval [a,b]
		fc = f(c);					// find value of function at midpoint
		if(ntol < fc && fc < tol)
		{
			break;					// Solution found within specified tolerance
		}
		else if (f(a)*fc < 0)				// f(c) and f(b) have the same sign
		{
			b = c;					// Update [a,b] --> [a,c]
		}
		else						// f(c) and f(a) have the same sign
		{
			a = c;					// Update [a,b] --> [c,b]
		}
	}

	// Output results
	if(i == N)						// Max number of iterations completed (solution not found)
	{
		cout << "The root could not be approximated to within " << tol << " tolerance in " << N << " iteration(s)." << endl;
		cout << "The current best guess is " << c << " yielding a function value of " << fc << "." << endl;
	}
	else							// solution found
	{
		cout << "The root was approximated to within " << tol << " tolerance in " << i+1 << " iteration(s)." << endl;
		cout << "The root is " << c << " yielding a function value of " << fc << "." << endl;
	}

	return 0; // End of the program
}
