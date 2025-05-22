import matplotlib.pyplot as plt
import numpy as np

# Data for plotting
data = np.loadtxt('average.txt')
n = data[:,0]
bXn = data[:,1]
mu = data[0,2]

fig = plt.figure(figsize=(12, 8), layout='tight')
ax = fig.add_subplot(111, projection='rectilinear')

ax.plot(n, bXn, linewidth = 3, label='Distribution')
ax.axhline(mu, linewidth = 3, linestyle = "--", color='k')

ax.set_xlabel('n', fontsize=20)
ax.set_ylabel('$\\bar{X}_n$', fontsize=20)
ax.set_xlim(-100,10000)
# ax.set_ylim(0.0,1.0)
ax.tick_params(axis='x', labelsize=20)
ax.tick_params(axis='y', labelsize=20)

ax.legend(fontsize=20)

# fig.savefig("test.png")
plt.show()
plt.close()