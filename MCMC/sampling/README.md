**Sampling with a Metropolis-Hastings Markov Chain Monte Carlo (MCMC)**

An MCMC method applied to sampling from a known density function using the Metropolis-Hastings algorithm.

sampling.cpp input(s):
   - Flag to indicate which density to sample, `D` (hard-coded).
   - Number of "burn-in time" iterations, `B` (hard-coded).
   - Number of Monte Carlo iterations, `I` (hard-coded).

sampling.cpp output(s):
   - Acceptance ratio of the chain, `A / I` (terminal-print).
   - `chain.txt` file with history of the chain.

plot_chain.py inputs(s):
   - `chain.txt` file with history of the chain (output from sampling.cpp).

plot_chain.py outputs(s):
   - Plots of the posterior distributions and chain history.
