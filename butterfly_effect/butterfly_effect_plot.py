# Plot butterfly effect results in 3D

from mpl_toolkits import mplot3d
import numpy as np
import matplotlib.pyplot as plt
import math

# Input parameters
sigma = 10
rho = 28
beta = 8.0/3

# Compute attractors
Att_x = np.array([math.sqrt(beta*(rho-1)),-math.sqrt(beta*(rho-1)),0])
Att_y = np.array([math.sqrt(beta*(rho-1)),-math.sqrt(beta*(rho-1)),0])
Att_z = np.array([rho-1,rho-1,0])

# Get data from file
traj_file = open("butterfly.txt", "r")
traj_x = []
traj_y = []
traj_z = []
traj_t = []
for line in traj_file:
	data = line.split()
	print(data)
	traj_x.append(float(data[0]))
	traj_y.append(float(data[1]))
	traj_z.append(float(data[2]))
	traj_t.append(float(data[3]))

traj_file.close()

# Convert to numpy arrays
traj_x = np.array(traj_x)
traj_y = np.array(traj_y)
traj_z = np.array(traj_z)
traj_t = np.array(traj_t)

# Plot trajectory and attractors
fig = plt.figure()
ax = plt.axes(projection='3d')
ax.plot3D(traj_x,traj_y,traj_z, 'blue')
ax.scatter3D(Att_x,Att_y,Att_z, color='red')
plt.show()
