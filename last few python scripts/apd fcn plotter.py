import numpy as np
import matplotlib.pylab as plt

xs = np.linspace(33,220,220-34)
plt.rcParams.update({'font.size': 22})
plt.figure()
plt.plot(xs[:33],np.ones(33)*33,"b", linewidth = 4)
plt.plot(xs[33: 61], 0.629*xs[33:61] - 8.9,"b", linewidth = 4)
plt.plot(xs[61:], np.ones(125)*50, "b",linewidth = 4)
plt.plot(xs[:61],np.ones(61)*50,"b--", linewidth = 4)
plt.xlabel( "Total Time Elapsed Since Depolarisation [dimensionless time]", size = 18 )
plt.ylabel( r"$\tau (x)$ [dimentionless time]", size = 22)
plt.axis
#plt.grid()
plt.show()