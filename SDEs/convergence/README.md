**Convergence Rates**

Illustrate convergence rates of various SDE solvers using geometric brownian motion (GBM). Currently, 4 methods with the respective (weak, strong) convergence rates are explored: Euler-Maruyama (1, 1/2), Milstein (1, 1), RK2 (1, 2), semi-implicit stochastic theta (1/2, 1/2).

convergence.cpp input(s):
   - Flag to either show trajectories or compute approximation errors, `MODE` (hard-coded).
   - Flag to indicate which method to use, `METHOD` (hard-coded).
   - Drift constant for GBM, `r` (hard-coded).
   - Diffusion constant for GBM, `alpha` (hard-coded).
   - Starting point of GBM, `GBM0` (hard-coded).
   - Number of realizations to average, `R` (hard-coded).
   - Number of time steps per realization, `N` (hard-coded).
   - Array with resolutions, `N_res` (hard-coded).
   - Final time to simulate, `T` (hard-coded).

convergence.cpp output(s):
   - If `MODE == 1`, one sample trajectory for the method indicated with `METHOD` at each resolution (terminal-print).
   - If `MODE == 2`, approximation error for the method indicated with `METHOD` at each resolution (terminal-print).