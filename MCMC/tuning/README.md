**Tuning a Markov Chain Monte Carlo (MCMC) Algorithm**

Multiple MCMC algorithms are tuned according to two heuristics, acceptance ratio and (windowed) integrated autocorrelation time.

tuning.cpp input(s):
   - Flag to indicate which density to sample, `D` (hard-coded).
   - Flag to indicate which algorithm to use, `S` (hard-coded).
   - Number of walkers to use in stretch-move algorithm, `K` (hard-coded).
   - Number of "burn-in time" iterations, `B` (hard-coded).
   - Number of Monte Carlo iterations, `I` (hard-coded).

tuning.cpp output(s):
   - `acceptance.txt` file with acceptance ratio for a range of the tunable parameter.
   - `autocorrelation.txt` file with integrated autocorrelation time for a range of the tunable parameter.

