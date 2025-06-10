**Predator-Prey Model**

Calculate the average behavior of a predator-prey model (continuous-time Markov chain) using both Gillespie and tau-leaping algorithms.

predator_prey.cpp input(s):
   - Initial population of prey, `H0` (user-input).
   - Initial population of predator, `L0` (user-input).
   - Prey natural birth-rate, `Rhb` (user-input).
   - Pray hunt-induced death-rate, 'Rhd' (user-input).
   - Predator hunt-induced birth-rate, `Rld` (user-input).
   - Predator natural death-rate, `Rld` (user-input).
   - Final time to simulate, `Tf` (user-input).
   - Flag for which method to use, `METHOD` (hard-coded).
   - Number of time points along which to discretize a realization, `N` (hard-coded).
   - Number of chain realizations for average, `R` (hard-coded).

predator_prey.cpp output(s):
   - `population.txt` file with the average populations.
