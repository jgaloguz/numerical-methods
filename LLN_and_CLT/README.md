**Law of Large Numbers and Central Limit Theorem**

Illustrate the Law of Large Numbers and the Central Limit Theorem, as well as instances where they do not hold.

LLN_and_CLT.cpp input(s):
   - Type of random variable to sample, `RV_TYPE` (hard-coded).
   - Distribution parameters, `param1` and `param2` (hard-coded).
   - Number of samples in each i.i.d. sequence, `N` (hard-coded).
   - Number of i.i.d. sequence realizations, `R` (hard-coded).

LLN_and_CLT.cpp output(s):
   - Mean and variance of i.i.d. random variables being sampled (terminal-print).
   - `average.txt` file with the normalized average as a function of sample index for one realization. The mean is also plotted as a constant value for reference.
   - `distro.txt` file with the binned distribution of the normalized average after all realizations. The pdf of a normal random variable is also plotted for reference.

plot_LLN.py input(s):
   - `average.txt` file with cumulative average over sample index.

plot_LLN.py output(s):
   - Plot of the cumulative average over sample index.

plot_CLT.py input(s):
   - `distro.txt` file with the binned distribution of the normalized cumulative average.

plot_CLT.py output(s):
   - Plot of the binned distribution of the normalized cumulative average.
