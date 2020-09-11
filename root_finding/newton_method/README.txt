

Newton's Algorithm: Find a zero of a given function within a specified interval (if exists).

secant.cpp input(s):
	- Function for which a root is desired, f(x) (hard-coded).
	- Derivative of the function for which a root is desired, df(x) (hard-coded).
	- Approximate solution to be used as the initial point of the iterative process (user-input).
	- Tolerance/precision with which to find the root, tol (hard-coded).  This means that whatever root, x, the code outputs should yield a function value, -tol < f(x) < tol.
	- Maximum number of iterations, N (user-input).

secant.cpp output(s):
	- If a root is found within the specified tolerance in N iterations or less, the root, function value, and number of iterations employed are outputed (terminal-print).
	- If a root is not found within the specified tolerance in N iterations or less, the best approximation of the root after N iterations, and the corresponding function value are outputed (terminal-print).

