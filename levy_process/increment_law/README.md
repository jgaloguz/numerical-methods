**Simulate Levy Process from Increments Law**

Simulate a Levy process (generalized random walk) given an analytic expression for the law of increments, i.e. a distribution for the process at each time.

increment_law.cpp input(s):
   - Final time to simulate, `T` (hard-coded).
   - Number of time points along which to discretize a realization, `N` (hard-coded).

increment_law.cpp output(s):
   - `random_walk.txt` file with a realization of the Levy process discretized in time.
