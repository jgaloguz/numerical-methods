**Simulate Compound Poisson Process**

Simulate a compound Poisson process through its jump rate and distribution.

increment_law.cpp input(s):
   - Jump rate of process, `R` (hard-coded).
   - Final time to simulate, `T` (hard-coded).
   - Number of time points along which to discretize a realization, `N` (hard-coded).

increment_law.cpp output(s):
   - `random_walk.txt` file with a realization of the Levy process discretized in time.
