Perceptron Algorithm: finds a hyperplane between two types of data points in a linearly separable data set (i.e. binary classification).

perceptron.cpp input(s):
   - Learning rate, `LR` (hard-coded).
   - `separable_set.txt` file containing the total number of data points, `N`, the dimension of the space, `K`, and all the points labeled in the corresponding category to which they belong.

perceptron.cpp output(s):
   - `hyperplane.txt` file containing the weights and bias for a hyperplane dividing the space according to the categories.

perceptron_plot.py input(s):
   - `separable_set.txt` (input for perceptron.cpp).
   - `hyperplane.txt` (output for perceptron.cpp).

perceptron_plot.py output(s):
   - plot of the data set (labeled with color) and the hyperplane dividing it (only available for 2 or 3 dimensions).

REMARKS:
   - This perceptron only works for a linearly separable set of data.  If the data provided is NOT separable, the algorithm is caught in an infinite loop.
