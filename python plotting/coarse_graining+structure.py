import numpy as np
#import layout
import matplotlib.pylab as plt
from mpl_toolkits.axes_grid1 import make_axes_locatable
import os

path = "0.17_restitution_200_healthy_pacemaker__100000.txt"


filenames = []

"""for f in os.listdir(path):
    if not f.startswith('.'):
        filenames.append(f)"""

horizontal = 100

total_time = 100000.
# = os.listdir(path)
runs = 4
num_nu = np.size(filenames)/runs
nu_min = 0.21
nu_max = .34
data = np.zeros((200,200))
fraction = np.zeros((num_nu,runs))
data = np.genfromtxt("0.15_fixed_restitution_structure_excited_200_healthy_pacemaker__100000.txt")
cells = np.zeros((200,200))
taus = np.zeros((200,200))
vcon = np.zeros((200,200))
functional = np.zeros((200,200))
for i in range (0,200):
    for j in range (0,200):
        cells[i,j] = 1 -data[j+200*i][1]/total_time
        vcon[i,j] = data[j+200*i][0]
        functional[i,j] = data[j+200*i][2]

structure = vcon + functional
    
#COARSEGRAIN BELOW
#try with a square coarse graining first

average = np.zeros((200,200))

for i in range (0,200):
    for j in range (0,200):
        n = 3
        b = 5
        if i<b/2:
            b=0
        if j<n/2:
            n=0
        if i +b/2 >199:
            b=0
        if j+n/2 >199:
            n=0
       # print np.average(cells[i:i+b+1,j:j+n+1])
        average[i][j] =np.average(cells[i-b/2:i+b/2+1,j-n/2:j+n/2+1])
        


# Four axes, returned as a 2-d array

test = ["ax1", "ax2", "ax3", "ax4"]

fig = plt.figure(1)
for idx in range(len(test)):
  vars()[test[idx]] = fig.add_subplot(2,2, (idx + 1))
  divider = make_axes_locatable(vars()[test[idx]])
  vars()["c" + test[idx]] = divider.append_axes("right", size = "5%", pad = 0.05)
  plt.subplots_adjust(hspace = .3, left = 0.1, wspace = 0.1)

im1 = ax1.imshow(cells)
plt.colorbar(im1, cax = cax1)
im2 = ax2.imshow(average)
plt.colorbar(im2, cax = cax2)

im3 = ax3.imshow(structure)
plt.colorbar(im3, cax = cax3)

im4 = ax4.imshow(vcon)
plt.colorbar(im4, cax = cax4)


plt.show()