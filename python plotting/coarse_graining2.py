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
data = np.genfromtxt("0.15_refractory_excited_light_restitution_200_healthy_pacemaker__100000.txt")
cells = np.zeros((200,200))
taus = np.zeros((200,200))
for i in range (0,200):
    for j in range (0,200):
        cells[i,j] = 1 -data[j+200*i][0]/total_time
        #taus[i,j] = data[j+200*i][1]/total_time
    
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
        
    

nu = np.linspace(nu_min,nu_max,num_nu)
plt.figure()
plt.pcolor(cells)
plt.colorbar()
#plt.xlabel("nu")
#plt.ylabel("P risk")
plt.title( "Fracion of time spent in excited regime for nu " )
plt.grid()
plt.show()

plt.figure()
plt.pcolor(average)
plt.colorbar()
#plt.xlabel("nu")
#plt.ylabel("P risk")
plt.title( "Coarse graining using rectangle of side 1/nu in x dir and 2 in y-dir " )
plt.grid()
plt.show()



