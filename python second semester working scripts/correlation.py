import numpy as np
from scipy import signal
#import layout
import matplotlib.pylab as plt
from mpl_toolkits.axes_grid1 import make_axes_locatable
from mpl_toolkits.mplot3d import Axes3D
import os


#1D
dynamics = np.genfromtxt("total_excited_fraction.txt")
structure = np.genfromtxt("avg_struct.txt")

dyn_norm = (dynamics - np.mean(dynamics))/np.std(dynamics)
struct_norm = (structure - np.mean(structure))/(np.std(structure)*len(structure)*len(structure))

rand1 = np.random.rand(4000)
rand1_norm = (rand1 - np.mean(rand1))/np.std(rand1)

corr = np.correlate(np.ndarray.flatten(dyn_norm),np.ndarray.flatten(struct_norm),"full")
corr1= np.correlate(rand1_norm,np.ndarray.flatten(structure),"same")


plt.figure()
plt.plot(corr,'g')
plt.show()


#2D
rand2 = np.random.rand(200,200)
rand2_norm = (rand2 - np.mean(rand2))/np.std(rand2)

corr2D = signal.correlate2d(dyn_norm, struct_norm,"same")
corr2D2 = signal.correlate2d(struct_norm, rand2_norm,"same")

hf = plt.figure()
ha = hf.add_subplot(111,projection = "3d")
x = range(200)
y=x
X, Y = np.meshgrid(x, y)  # `plot_surface` expects `x` and `y` data to be 2D
ha.plot_surface(X, Y, corr2D)

plt.show()