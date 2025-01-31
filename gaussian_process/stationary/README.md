**Stationary Gaussian Process**

Simulate a stationary Gaussian process given with zero mean and a valid 1D covariance function. Covariance functions MUST be symmetric (even), decaying from zero (i.e. C(t) <= C(0) for all t), and positive-semidefinite. By Bochner's Theorem, the inverse Fourier Transform of a non-negative function is positive-semidefinite.

stationary_gaussian.cpp input(s):
   - Final time to simulate, `L` (user-input).
   - Number of time points, `N` (user-input).

stationary_gaussian.cpp output(s):
   - `stationary_gaussian.txt` file with a realization of the process.