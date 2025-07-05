**Euler Maruyama Method**

Solve an SDE using the 1D Euler-Maruyama method.

euler_maruyama.cpp input(s):
   - Number of realizations to average, `R` (hard-coded).
   - Number of time steps per realization, `N` (hard-coded).
   - Drift parameter, `a` (user-input).
   - Diffusion parameter, `s` (user-input).
   - Final time to simulate, `T` (user-input).

euler_maruyama.cpp output(s):
   - `trajectory.txt` file a sample trajectory.
   - `moments.txt` file with the mean and variance.