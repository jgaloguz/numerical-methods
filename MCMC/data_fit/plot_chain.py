# Import libraries
import numpy as np
import matplotlib.pyplot as plt

# Import chain
state_history = np.loadtxt("chain.txt")
M = np.size(state_history, 1)

# Plot posterior distribution and its marginals
for i in range(M):
   fig = plt.figure(figsize=(16, 8), layout='tight')
   fig.suptitle("Parameter {:d}".format(i+1), fontsize=36)

   ax1 = fig.add_subplot(121, projection='rectilinear')
   ax1.set_title('Chain Evolution (after burn-in)', fontsize=24)
   ax1.plot(state_history[:,i])

   ax2 = fig.add_subplot(122, projection='rectilinear')
   ax2.set_title('Posterior Distribution (unnormalized)', fontsize=24)
   ax2.hist(state_history[:,i], bins=50)

   plt.show()
   plt.close(fig)
