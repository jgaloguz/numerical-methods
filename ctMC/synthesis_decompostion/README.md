**Synthesis-Decomposition Reaction**

Calculate the average behavior of a synthesis-decomposition reaction, A + B <--> C, (continuous-time Markov chain) using the tau-leaping algorithm.

synthesis_decomposition.cpp input(s):
   - Initial population of specie A, `A0` (user-input).
   - Initial population of specie B, `B0` (user-input).
   - Initial population of specie C, `C0` (user-input).
   - Synthesis reaction rate, `Rs` (user-input).
   - Decomposition reaction rate, `Rd` (user-input).
   - Final time to simulate, `Tf` (user-input).

synthesis_decomposition.cpp output(s):
   - `reaction.txt` file with the average number of species over time.
