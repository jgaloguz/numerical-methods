**Bisection Method**

Find a zero of a given function within a specified interval (if exists).

bisection.cpp input(s):
   - Function for which a root is desired, `f(x)` (hard-coded).
   - Left and right bound of interval containing at least one zero, `a`, `b` (user-input).  The signs of the values of the function at each endpoint must be opposites.
   - Tolerance/precision with which to find the root, `tol` (hard-coded).  This means that whatever root, `c`, the code outputs should yield a function value, `-tol` < `f(c)` < `tol`.
   - Maximum number of iterations, `N` (user-input).

bisection.cpp output(s):
   - If a root is found within the specified tolerance in `N` iterations or less, the root, function value, and number of iterations employed are outputed (terminal-print).
   - If a root is not found within the specified tolerance in `N` iterations or less, the best approximation of the root after `N` iterations, and the corresponding function value are outputed (terminal-print).
