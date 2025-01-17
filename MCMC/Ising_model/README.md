**Markov Chain Monte Carlo (MCMC)**

An MCMC method applied to finding the critical (phase-change) temperature of a square 2D Ising-lattice of locally, isotropically interacting magnetic spins without an external magnetic field.

ising_model.cpp input(s):
   - Number of lattice sites per side of the square lattice, `N` (hard-coded).

ising_model.cpp output(s):
   - `M_vs_T.dat` file containing the average magnetization for a range of temperatures. The temperature, `T`, at which the magnetization, `M`, suddenly decreases from ~1 to ~0 is the critical temperature. This file may be directly inputed to any suitable 2D graphing software for vizualization, such as xmgrace.
