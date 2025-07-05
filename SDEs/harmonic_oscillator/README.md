**Stochastically Forced Harmonic Oscillator**

Solve the SDE for a stochastically forced harmonic oscillator using the 2D Euler-Maruyama method.

harmonic_oscillator.cpp input(s):
   - Number of realizations to average, `R` (hard-coded).
   - Number of time steps per realization, `N` (hard-coded).
   - Mass, `m` (user-input).
   - Damping factor, `y` (user-input).
   - Spring constant, `k` (user-input).
   - White noise factor, `s` (user-input).
   - Final time to simulate, `T` (user-input).

harmonic_oscillator.cpp output(s):
   - `trajectory.txt` file a sample trajectory.
   - `moments.txt` file with the mean and variance.
   - `spectrum.txt` file with the spectral density of oscillations.