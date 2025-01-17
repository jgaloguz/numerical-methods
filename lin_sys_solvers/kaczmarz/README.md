**Kaczmarz Algorithm**

Approximately solve a user specified linear system of equations, Ax = b, (of order `N`) to a specified degree of accuracy through an iterative procedure.

kaczmarz.cpp input(s):
   - `system.txt` file, containing the system to be solved.  This file has the order of the system, `N`, in the first line, along with the entries of `A`, one row per line, with the corresponding entries of `b` at the end of each row.
   - desired accuracy for approximate solution, `eps` (hard-coded).
   - maximum number of iterations, `max_iter` (hard-coded).

kaczmarz.cpp output(s):
   - Approximate solution to the system (terminal-print).
   - `iterations.txt`, containing all approximations made during the iterative procedure.