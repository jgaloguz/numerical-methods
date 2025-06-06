**Birth-Death Process**

Calculate the average behavior of a birth-death process (continuous-time Markov chain) using the Doob-Gillespie algorithm.

birth_death.cpp input(s):
   - Initial population, `X0` (user-input).
   - Birth rate, `Rb` (user-input).
   - Death rate, `Rd` (user-input).
   - Final time to simulate, `Tf` (user-input).
   - Number of time points along which to discretize a realization, `N` (hard-coded).
   - Number of chain realizations for average, `R` (hard-coded).

birth_death.cpp output(s):
   - `population.txt` file with the average population over time.
