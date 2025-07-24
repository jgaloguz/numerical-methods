import matplotlib.pyplot as plt
import numpy as np
import random as rd

# Plot results of forward and backward methods
anal1 = np.loadtxt('analytic1.txt')
anal2 = np.loadtxt('analytic2.txt')
forw1 = np.loadtxt('forward1.txt')
forw2 = np.loadtxt('forward2.txt')
back1 = np.loadtxt('backward1.txt')
back2 = np.loadtxt('backward2.txt')

fig = plt.figure(figsize=(12, 8), layout='tight')
ax = fig.add_subplot(111, projection='rectilinear')

ax.plot(anal1[:,0], anal1[:,1], color = 'k',
        linewidth = 3, linestyle = '-', label='IC (Analytic)')
ax.plot(anal2[:,0], anal2[:,1], color = 'k',
        linewidth = 3, linestyle = '--', label='Solution (Analytic)')
ax.plot(forw1[:,0], forw1[:,1], color = 'tab:blue',
        linewidth = 3, linestyle = '--', label='IC (Forward)')
ax.plot(forw2[:,0], forw2[:,1], color = 'tab:blue',
        linewidth = 3, linestyle = ':', label='Solution (Forward)')
ax.plot(back1[:,0], back1[:,1], color = 'tab:red',
        linewidth = 3, linestyle = '--', label='NOT IC (Backward)')
ax.plot(back2[:,0], back2[:,1], color = 'tab:red',
        linewidth = 3, linestyle = ':', label='Solution (Backward)')

ax.set_xlim(-10.0,10.0)
ax.set_xlabel('$x$', fontsize=20)
ax.set_ylabel('$F(t,x)$', fontsize=20)
ax.tick_params(axis='x', labelsize=20)
ax.tick_params(axis='y', labelsize=20)

ax.legend(fontsize=20)

# fig.savefig("test.png")
plt.show()
plt.close()

# Plot a few sample pseudo-trajectories from forward and backward methods
traj_forw = np.loadtxt('traj_forw.txt')
traj_back = np.loadtxt('traj_back.txt')
n_traj = np.size(traj_forw, 0)

fig = plt.figure(figsize=(12, 8), layout='tight')
ax = fig.add_subplot(111, projection='rectilinear')

rand_t = rd.randint(0, n_traj)
ax.plot(traj_forw[rand_t,:], color = 'tab:blue',
        linewidth = 3, linestyle = '-', label='forward')
ax.plot(traj_back[rand_t,:], color = 'tab:red',
        linewidth = 3, linestyle = '-', label='backward')
for i in range(1,5):
   ax.plot(traj_forw[rand_t + i,:], color = 'tab:blue',
           linewidth = 3, linestyle = '-')
   ax.plot(traj_back[rand_t + i,:], color = 'tab:red',
           linewidth = 3, linestyle = '-')

ax.set_xlabel('$t$ index', fontsize=20)
ax.set_ylabel('$x$', fontsize=20)
ax.tick_params(axis='x', labelsize=20)
ax.tick_params(axis='y', labelsize=20)

ax.legend(fontsize=20)

# fig.savefig("test.png")
plt.show()
plt.close()