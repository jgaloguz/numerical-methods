import matplotlib.pyplot as plt
import numpy as np

# Data for plotting
data = np.loadtxt('distro.txt')
x = data[:,0]
Sn = data[:,1]
N01 = data[:,2]

fig = plt.figure(figsize=(12, 8), layout='tight')
ax = fig.add_subplot(111, projection='rectilinear')

ax.step(x, Sn, where="post", linewidth = 3, label='n = 10000')
ax.plot(x, N01, linewidth = 3, linestyle = '--', label='Normal(0,1)')

ax.set_xlabel('x', fontsize=20)
ax.set_ylabel('PDF of $S_n$', fontsize=20)
ax.set_xlim(-5.0,5.0)
ax.set_ylim(0,0.5)
ax.tick_params(axis='x', labelsize=20)
ax.tick_params(axis='y', labelsize=20)

ax.legend(fontsize=20)

# fig.savefig("test.png")
plt.show()
plt.close()