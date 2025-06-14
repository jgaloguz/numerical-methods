# Import libraries
import numpy as np
import matplotlib.pyplot as plt
import random

# Import chain
data = np.loadtxt("data.txt", skiprows=1)
state_history = np.loadtxt("chain.txt")
I = np.size(state_history, 0)
M = np.size(state_history, 1)

# 2D density plot for samples
fig = plt.figure(figsize=(10, 10), layout='tight')

ax = fig.add_subplot(111, projection='rectilinear')
ax.hist2d(state_history[:,0], state_history[:,1], bins=(100, 100), cmap=plt.cm.jet)
ax.set_xlabel("Parameter 1", fontsize=24)
ax.set_ylabel("Parameter 2", fontsize=24)
ax.tick_params(axis='both', labelsize=16)

plt.savefig("2D_hist.png", dpi=300)
plt.close(fig)

# Plot posterior distribution marginals and chain history
for i in range(M):
   fig = plt.figure(figsize=(10, 10), layout='tight')

   ax1 = fig.add_subplot(111, projection='rectilinear')
   ax1.set_xlabel("Iteration (after burn-in)", fontsize=24)
   ax1.set_ylabel("Parameter {:d}".format(i+1), fontsize=24)
   ax1.tick_params(axis='both', labelsize=16)
   ax1.scatter(np.arange(0,I), state_history[:,i], s=1)

   plt.savefig("chain_parameter_{:d}.png".format(i+1), dpi=300)
   plt.close(fig)

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

# Plot model with data using a few random samples from the chain
X = np.linspace(11.0,19.5,num=50)
fig = plt.figure(figsize=(10, 10), layout='tight')

ax = fig.add_subplot(111, projection='rectilinear')
for i in range(10):
   sample = random.randint(0,I)
   Y = np.ones(50) * state_history[sample, 0]
   for j in range(1,M):
      Y = Y + state_history[sample, j] * np.power(X, j)
   if i == 0:
      ax.plot(X, Y, 'r--', linewidth=2, label='sample models')
   else:
      ax.plot(X, Y, 'r--', linewidth=2)
ax.errorbar(data[:,0], data[:,1], yerr = data[:,2], fmt ='o', linestyle='',
            elinewidth=2, capsize=5, capthick=2, markersize=10, label='data')
ax.set_xlabel("x", fontsize=24)
ax.set_ylabel("y", fontsize=24)
ax.tick_params(axis='both', labelsize=16)
ax.legend(loc=2, fontsize=20)

plt.savefig("sample_fits.png", dpi=300)
plt.close(fig)