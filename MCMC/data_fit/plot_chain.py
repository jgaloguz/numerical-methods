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

plt.show()
plt.close(fig)

# Plot posterior distribution and its marginals
for i in range(M):
   fig = plt.figure(figsize=(16, 8), layout='tight')
   fig.suptitle("Parameter {:d}".format(i+1), fontsize=36)

   ax1 = fig.add_subplot(121, projection='rectilinear')
   ax1.set_xlabel("Iteration (after burn-in)", fontsize=24)
   ax1.set_ylabel("Value", fontsize=24)
   ax1.tick_params(axis='both', labelsize=16)
   ax1.scatter(np.arange(0,I), state_history[:,i], s=1)

   ax2 = fig.add_subplot(122, projection='rectilinear')
   ax2.set_xlabel("Value", fontsize=24)
   ax2.set_ylabel("Posterior (unnormalized)", fontsize=24)
   ax2.tick_params(axis='both', labelsize=16)
   ax2.hist(state_history[:,i], bins=50)
   ax2.axvline(np.percentile(state_history[:,i], 16.0), color='black', linestyle='--')
   ax2.axvline(np.percentile(state_history[:,i], 50.0), color='red', linestyle='--')
   ax2.axvline(np.percentile(state_history[:,i], 84.0), color='black', linestyle='--')

   plt.show()
   plt.close(fig)


# Plot model with data using a few random samples from the chain
X = np.linspace(11.0,19.5,num=50)
fig = plt.figure(figsize=(16, 8), layout='tight')

ax = fig.add_subplot(111, projection='rectilinear')
for i in range(10):
   sample = random.randint(0,I)
   Y = np.ones(50) * state_history[sample, 0]
   for j in range(1,M):
      Y = Y + state_history[sample, j] * np.power(X, j)
   ax.plot(X, Y, 'r--', linewidth=2)
ax.errorbar(data[:,0], data[:,1], yerr = data[:,2], fmt ='o', linestyle='',
            elinewidth=2, capsize=5, capthick=2, markersize=10)
ax.set_xlabel("x", fontsize=24)
ax.set_ylabel("y", fontsize=24)
ax.tick_params(axis='both', labelsize=16)

plt.show()
plt.close(fig)