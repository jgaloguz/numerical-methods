# Plot results from perceptron analysis (in 2 or 3 dimensions)

# Import libraries
import numpy as np
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d as p3
import math

# Import data
data_file = open("separable_set.txt", "r")            # Open file with data
params = data_file.readline().split()                 # Read first line (to get the parameters of the data)
N = int(params[0])                                    # Number of data points
K = int(params[1])                                    # Dimensionality

class1 = []                                           # Empty array for class 1
class2 = []                                           # Empty array for class 2
for i in range(N):
   vector = data_file.readline().split()              # Read in data for a vector
   if int(vector[K]) == 0:                            # If vector is class 1
      vec = [float(vector[j]) for j in range(K)]
      class1.append(vec)
   if int(vector[K]) == 1:                            # If vector is class 2
      vec = [float(vector[j]) for j in range(K)]
      class2.append(vec)
data_file.close()                                     # Close file with data
class1 = np.array(class1)
class2 = np.array(class2)

# Import hyperplane
hyperplane_file = open("hyperplane.txt", "r")         # Open hyperplane file
bias = float(hyperplane_file.readline())              # Read in bias
weights = []                                          # Weights vector
weights_text = hyperplane_file.readline().split()     # Read in weights
for i in range(K):
   weights.append(float(weights_text[i]))
hyperplane_file.close()                               # Close hyperplane file

# Find hyperplane
if K == 2:                                # In 2 dimensions
   # Find bounds for plotting
   x_max = np.max([np.max(class1[:,0]),np.max(class2[:,0])])
   x_min = np.min([np.min(class1[:,0]),np.min(class2[:,0])])
   y_max = np.max([np.max(class1[:,1]),np.max(class2[:,1])])
   y_min = np.min([np.min(class1[:,1]),np.min(class2[:,1])])
   if weights[1] == 0:
      x = -bias/weights[0]
      X = [x,x]
      Y = [y_min,y_max]
   else:
      n_x = -weights[0]/weights[1]
      d = -bias/weights[1]
      X = [x_min,x_max]
      Y = [n_x*x_min + d, n_x*x_max + d]
   # Plot results
   fig, ax = plt.subplots(1,1)
   ax.scatter(class1[:,0],class1[:,1],c='blue')
   ax.scatter(class2[:,0],class2[:,1],c='red')
   ax.plot(X,Y,'g--')
   ax.set(xlim = [x_min-1,x_max+1], ylim = [y_min-1,y_max+1])

   plt.show()
   plt.close(fig)
elif K == 3:                              # In 3 dimensions
   # Find bounds for plotting
   x_max = np.max([np.max(class1[:,0]),np.max(class2[:,0])])
   x_min = np.min([np.min(class1[:,0]),np.min(class2[:,0])])
   y_max = np.max([np.max(class1[:,1]),np.max(class2[:,1])])
   y_min = np.min([np.min(class1[:,1]),np.min(class2[:,1])])
   z_max = np.max([np.max(class1[:,2]),np.max(class2[:,2])])
   z_min = np.min([np.min(class1[:,2]),np.min(class2[:,2])])
   if weights[2] == 0:
      if weights[1] == 0:
         x = -bias/weights[0]
         X = [x,x]
         Y = [y_min,y_max]
         xx, yy = np.meshgrid(X,Y)
         zz = np.array([[z_min,z_min],[z_max,z_max]])
      else:
         n_x = -weights[0]/weights[1]
         d = -bias/weights[1]
         X = [x_min,x_max]
         Y = [n_x*x_min + d, n_x*x_max + d]
         xx, yy = np.meshgrid(X,Y)
         zz = np.array([[z_min,z_min],[z_max,z_max]])
   else:
      n_x = -weights[0]/weights[2]
      n_y = -weights[1]/weights[2]
      d = -bias/weights[2]
      X = [x_min,x_max]
      Y = [y_min,y_max]
      xx, yy = np.meshgrid(X,Y)
      zz = n_x*xx + n_y*yy + d
   # Plot results
   fig = plt.figure()
   ax = plt.axes(projection='3d')
   ax.scatter3D(class1[:,0],class1[:,1],class1[:,2], color='blue')
   ax.scatter3D(class2[:,0],class2[:,1],class2[:,2], color='red')
   ax.plot_surface(xx,yy,zz,alpha=0.5,color='g')
   plt.show()
   plt.close(fig)
else:
   print("Can only visualize hyperplane in 2 or 3 dimensions") # Message if dimension is not apt for visualization
