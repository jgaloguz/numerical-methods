# Import libraries
import numpy as np
import matplotlib.pyplot as plt
import random

# Import chain
state_history = np.loadtxt("chain.txt")
I = np.size(state_history, 0)
M = np.size(state_history, 1)

# 2D density plot for samples
fig = plt.figure(figsize=(10, 10), layout='tight')

ax = fig.add_subplot(111, projection='rectilinear')
ax.hist2d(state_history[:,0], state_history[:,1], bins=(200, 200), cmap=plt.cm.jet)
ax.set_xlabel("Parameter 1", fontsize=24)
ax.set_ylabel("Parameter 2", fontsize=24)
ax.tick_params(axis='both', labelsize=16)

plt.savefig("2D_hist.png", dpi=300)
plt.close(fig)

# Plot posterior distribution marginals
for i in range(M):
   fig = plt.figure(figsize=(10, 10), layout='tight')

   ax2 = fig.add_subplot(111, projection='rectilinear')
   ax2.set_xlabel("Parameter {:d}".format(i+1), fontsize=24)
   ax2.set_ylabel("Posterior (unnormalized)", fontsize=24)
   ax2.tick_params(axis='both', labelsize=16)
   ax2.hist(state_history[:,i], bins=50)
   ax2.axvline(np.percentile(state_history[:,i], 16.0), color='black', linestyle='--')
   ax2.axvline(np.percentile(state_history[:,i], 50.0), color='red', linestyle='--')
   ax2.axvline(np.percentile(state_history[:,i], 84.0), color='black', linestyle='--')
   if (i % 2) == 1:
      ax2.xaxis.tick_top()
      ax2.xaxis.set_label_position("top")
      ax2.set_xlabel("Parameter {:d}".format(i+1), labelpad=10, fontsize=24)
      ax2.set_ylabel("Posterior (unnormalized)", rotation=270, va='top', fontsize=24)


   plt.savefig("posterior_parameter_{:d}.png".format(i+1), dpi=300)
   plt.close(fig)

# Plot chain history
fig = plt.figure(figsize=(10, 10), layout='tight')

ax1 = fig.add_subplot(211, projection='rectilinear')
ax1.set_ylabel("Parameter 2", fontsize=24)
ax1.tick_params(axis='both', labelsize=16)
ax1.scatter(np.arange(0,I), state_history[:,1], s=1)

ax2 = fig.add_subplot(212, projection='rectilinear')
ax2.set_xlabel("Iteration (after burn-in)", fontsize=24)
ax2.set_ylabel("Parameter 1", fontsize=24)
ax2.tick_params(axis='both', labelsize=16)
ax2.scatter(np.arange(0,I), state_history[:,0], s=1)

plt.savefig("chain_parameters.png".format(i+1), dpi=300)
plt.close(fig)

fig = plt.figure(figsize=(10, 10), layout='tight')