import matplotlib as mpl
from matplotlib import cm
import matplotlib.pyplot as plt
import numpy as np
import random as rd

# Plot results of Feynman-Kac and Crank-Nicolson schemes
crank_nicolson = np.loadtxt('crank_nicolson.txt')
feynman_kac = np.loadtxt('feynman_kac.txt')

fig = plt.figure(figsize=(12, 8), layout='tight')
ax = fig.add_subplot(111, projection='rectilinear')

ax.plot(crank_nicolson[:,0], crank_nicolson[:,1], color = 'k',
        linewidth = 3, linestyle = '-', label='Crank-Nicolson')
ax.plot(feynman_kac[:,0], feynman_kac[:,1], color = 'tab:red',
        linewidth = 3, linestyle = '--', label='Feynman-Kac')

ax.set_xlim(-1.0,1.0)
ax.set_xlabel('$x$', fontsize=20)
ax.set_ylabel('$F(1,x)$', fontsize=20)
ax.tick_params(axis='x', labelsize=20)
ax.tick_params(axis='y', labelsize=20)

ax.legend(fontsize=20)

# fig.savefig("test.png")
plt.show()
plt.close()

# Plot a few sample pseudo-trajectories from forward and backward methods
trajs = []
n_time = 0
traj_file = open('trajs.txt', 'r')
n_traj_max = 1000
for line in traj_file:
        n_traj_max = n_traj_max - 1
        trajs.append([])
        str_numbers = line.strip().split()
        for number in str_numbers:
                trajs[-1].append(float(number))
        trajs[-1] = np.array(trajs[-1])
        n_time_tmp = np.size(trajs[-1])
        if n_time_tmp > n_time:
                n_time = n_time_tmp
        if n_traj_max == 0:
                break
traj_file.close()
n_traj = len(trajs)

amps = []
maxQ = 0.0
amp_file = open('amps.txt', 'r')
for line in amp_file:
        amps.append([])
        str_numbers = line.strip().split()
        for number in str_numbers:
                amps[-1].append(float(number))
        amps[-1] = np.array(amps[-1])
        maxQ_tmp = np.max(amps[-1])
        if maxQ_tmp > maxQ:
                maxQ = maxQ_tmp
amp_file.close()

fig = plt.figure(figsize=(12, 8), layout='tight')
ax = fig.add_subplot(111, projection='rectilinear')

rand_t = rd.randint(0, n_traj)
ax.scatter(np.arange(np.size(trajs[rand_t])), trajs[rand_t], c=cm.turbo(np.abs(amps[rand_t])), s=0.1)
for i in range(1,5):
   ax.scatter(np.arange(np.size(trajs[rand_t+i])), trajs[rand_t+i], c=cm.turbo(np.abs(amps[rand_t + i])), s=0.1)
cbar = plt.colorbar(cm.ScalarMappable(norm=mpl.colors.Normalize(0, maxQ), cmap=cm.turbo), ax=ax)
cbar.ax.tick_params(labelsize=24)
cbar.set_label("Amplitude",fontsize=24)

ax.set_xlabel('$t$ index', fontsize=20)
ax.set_ylabel('$x$', fontsize=20)
ax.set_xlim(0,n_time)
ax.set_ylim(-1.0,1.0)
ax.tick_params(axis='x', labelsize=20)
ax.tick_params(axis='y', labelsize=20)
ax.axhline(-0.5, color = 'k', linestyle='--')
ax.axhline(0.0, color = 'k', linestyle='--')

# fig.savefig("test.png")
plt.show()
plt.close()