Thomas Algorithm: Solve a user specified banded, linear system of equations, Ax = b, (of order N and bandwith W).

thomas.cpp input(s):
	- system.txt file, containing the system to be solved.  This file has the order of the system, N, in the first line, the bandwith, W, in the second line, along with the entries of A, one row per line, with the corresponding entries of b at the end of each row.  Note that the system must have a unique solution and diagonal values should never be zero during the algebraic manipulations for the code to function properly.

thomas.cpp output(s):
	- Unique solution to the system (terminal-print).
