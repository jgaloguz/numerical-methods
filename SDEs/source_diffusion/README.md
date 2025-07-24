**Source-Diffusion**

Illustrate the Feynman-Kac method to solve SDEs using a diffusion PDE with constant coefficients and a source term.

source_diffusion.cpp input(s):
   - Diffusion coefficient, `D` (hard-coded).
   - Final time, `Tf` (hard-coded).
   - Number of time steps, `Nt` (hard-coded).
   - Number of particles per bin, `Np` (hard-coded).
   - Left boundary value, `LBC` (hard-coded).
   - Right boundary value, `RBC` (hard-coded).
   - Spatial coordinate to start binning, `Xi` (hard-coded).
   - Spatial coordinate to end binning, `Xf` (hard-coded).
   - Number of spatial bins, `Nx` (hard-coded).

source_diffusion.cpp output(s):
   - `feynman_kack.txt` file with numerical solution using the Feynman-Kac method (stochastic).
   - `crank_nicolson.txt` file with numerical solution using the Crank-Nicolson method (finite-difference).
   - `trajs.txt` file with trajectories sampled in the middle bin.

source_diffusion.py input(s):
   - `feynman_kack.txt` file.
   - `crank_nicolson.txt` file.
   - `trajs.txt` file.

source_diffusion.py output(s):
   - Plot of the approximate solution to the source-diffusion equation using the Feynman-Kac approach, as well as the Crank-Nicolson method for comparison.
   - Sample pseudo-trajectories used in the stochastic method, colored by path amplitude.