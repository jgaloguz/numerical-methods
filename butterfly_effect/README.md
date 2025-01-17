**Butterfly Effect**

RK4 method applied to solving the Lorenz (atmospheric convection) model.

butterfly_effect.cpp input(s):
   - Number of iterations, `N` (hard-coded).
   - Coupled ODE parameters, `sigma`, `rho`, `beta` (hard-coded).
   - Initial condition, `x0`, `y0`, `z0`, `t` (hard-coded).
   - Time step, `dt` (hard-coded).

butterly_effect.cpp output(s):
   - `butterly.txt` file containing x, y, z coordinates (columns 1, 2, 3, respectively) along with the corresponding time (column 4) describing the solution to the Lorentz problem.

butterfly_effect_plot.py input(s):
   - Coupled ODE parameters, `sigma`, `rho`, `beta` (hard-coded).
   - `butterfly.txt` file (output from butterfly_effect.cpp).

butterfly_effect_plot.py output(s):
   - 3D graph showing the solution to the Lorenz problem recorded in `butterfly.txt` (in blue), along with the stationary points ("attractors") of the coupled ODE system for the given parameters (in red).
