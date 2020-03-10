Gauss-Legendre Integration Algorithm: perform Guass-Legendre integration on a given function.  Result is exact for polynomials (in this code only for polynomials of degree 19 or less).

gauss_leg_quad_integ.cpp input(s):
	- Lower and upper bounds of integration, a, b (user-input).
	- Function to be integrated, f(x) (hard-coded).
	- Degree of polynomial, N (user-input).  This determines the number of terms to be used in the weighted sum computed to approximate the integral.  If the true degree of the polynomial in f(x) is equal to or less than N, the result will be exact.
	- Quadrature points and weights (from the gauss_leg_quad.txt and gauss_leg_quad_wts.txt files).

gauss_leg_quad_integ.cpp output(s):
	- Approximated or exact value of the integral (terminal-print).
