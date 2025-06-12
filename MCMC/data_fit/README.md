**Polynomial Regression with Markov Chain Monte Carlo (MCMC)**

An MCMC method applied to "fitting" data with a polynomial model using a Bayesian maximum-likelihood approach. More precisely, MCMC allows probabilistic inference of likely parameters given data and an a priori model.

poly_fit.cpp input(s):
   - `data.txt` file, containing the data to be fit by a model. This file has the total number of samples, `N`, in the first line and one sample per line after that. The format of the samples is `x y s` (whitespace separated) where `x` is the dependent variable, `y` is the independent variable, and `s` is the uncertainty in the data.
   - Degree of polynomial to use in fit, `M` (user-input).
   - Lower bound for the prior distribution of each parameter, `lb` (user-input).
   - Upper bound for the prior distribution of each parameter, `ub` (user-input).
   - Number of "burn-in time" iterations, `B` (hard-coded).
   - Number of Monte Carlo iterations, `I` (hard-coded).

poly_fit.cpp output(s):
   - Acceptance ratio of the chain, `A / I` (terminal-print).
   - `chain.txt` file with history of the chain.

plot_chain.py inputs(s):
   - `chain.txt` file with history of the chain (output from poly_fit.cpp).

plot_chain.py outputs(s):
   - Plots of the posterior distributions, chain history, and predicted models from sample paramters.
