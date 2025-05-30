**Simple Markov Chain Weather Model**

Simple discrete-time, finite state space, time-homogeneous Markov chain to forecast daily weather.

weather.cpp input(s):
   - Probability that tomorrow is cloudy given that today is sunny, `Psc` (hard-coded).
   - Probability that tomorrow is rainy given that today is sunny, `Psr` (hard-coded).
   - Probability that tomorrow is sunny given that today is cloudy, `Pcs` (hard-coded).
   - Probability that tomorrow is rainy given that today is cloudy, `Pcr` (hard-coded).
   - Probability that tomorrow is sunny given that today is rainy, `Prs` (hard-coded).
   - Probability that tomorrow is cloudy given that today is rainy, `Prc` (hard-coded).
   - How many days to simulate, `N` (user-input).
   - Today's weather, `Xn` (user-input).

weather.cpp output(s):
   - `forecast.dat` file with forecasted weather for `N` days.
   - Estimate of limiting distribution from forecast after `N` days (terminal-print).
   - Estimate of limiting distribution from `N`-step transition matrix (terminal-print).
