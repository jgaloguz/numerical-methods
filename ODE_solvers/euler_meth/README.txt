Euler-Taylor Algorithm: Solve given ODE (of order n) with specified initial condition (given in standard form).

nth_deg_euler.cpp input(s):
	- ODE to be solved, ODE(Y,x) (hard-coded).
	- Degree of the ODE to be solved, N (user-input).
	- Initial condition, a, Y, Y', Y'', ... , Y^(N-1).
	- Final x-coordinate at which to compute solution, b (user-input).

nth_deg_euler.cpp output(s):
	- solution.txt file containing approximated solution x, y (columns 1, 2, respectively) from a to b of given ODE with specified initial condition.  This file may be directly inputed to any suitable 2D graphing software for vizualization, such as xmgrace.
