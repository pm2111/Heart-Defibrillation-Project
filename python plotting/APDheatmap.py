import numpy as np
import matplotlib.pyplot as plt
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
data = np.genfromtxt("0.15_refractory_excited_restitution_200_healthy_pacemaker__100000.txt")
cells = np.zeros((200,200))
taus = np.zeros((200,200))
for i in range (0,200):
    for j in range (0,200):
        cells[i,j] = 1 -data[j+200*i][0]/total_time
        taus[i,j] = data[j+200*i][1]/total_time
    
    
    


nu = np.linspace(nu_min,nu_max,num_nu)
plt.figure()
plt.pcolor(cells)
plt.colorbar()
#plt.xlabel("nu")
#plt.ylabel("P risk")
plt.title( "Fracion of time spent in excited regime for nu = " )
plt.grid()
plt.show()
plt.figure()
plt.pcolor(-taus)
plt.colorbar()
#plt.xlabel("nu")
#plt.ylabel("P risk")
plt.title( "<tau> distribution after 10^5 time steps" )
plt.grid()
plt.show()




#LOOK FOR:
#average duration of episode (counter)
#P risk: add column and divide by time (length of array)
