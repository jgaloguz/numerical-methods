**Drift-Diffusion**

Illustrate the equivalence of the forward and backward methods to solve SDEs using a drift-diffusion PDE with constant coefficients and an intial Gaussian profile.
This code also highlights the importance of proper binning in the backward method as proof that it is not equivalent to physically propagating particles "backwards in time".

drift_diffusion.cpp input(s):
   - Diffusion coefficient, `D` (hard-coded).
   - Drift coefficient, `u` (hard-coded).
   - Initial time, `Ti` (hard-coded).
   - Final time, `Tf` (hard-coded).
   - Number of time steps, `Nt` (hard-coded).
   - Number of particles, `Np` (hard-coded).
   - Spatial coordinate to start binning, `Xi` (hard-coded).
   - Spatial coordinate to end binning, `Xf` (hard-coded).
   - Number of spatial bins, `Nx` (hard-coded).

drift_diffusion.cpp output(s):
   - `forward1.txt` file with the initial (sampled) distribution of particles from a forward simulation at time `Nt1`.
   - `forward2.txt` file with the final distribution of particles from a forward simulation at time `Nt2`.
   - `backward1.txt` file with an incorrectly weighted distribution of particles from a backward simulation at time `Nt2`.
   - `backward2.txt` file with a properly weighted distribution of particles from a backward simulation at time `Nt2`.
   - `traj_forw.txt` file with stochastic trajectories in the forward method.
   - `traj_back.txt` file with stochastic trajectories in the backward method.