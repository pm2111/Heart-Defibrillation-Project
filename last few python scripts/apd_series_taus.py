import numpy as np
import matplotlib.pyplot as plt
import os

path = "/Users/petermarinov/msci project/all code/ecg rotor no rotor/rotor tau/"
filenames = []

for f in os.listdir(path):
    if not f.startswith('.'):
        filenames.append(f)

filenames = np.sort(filenames)
total_time = 10000. 

data = np.zeros((200,200))
#data = np.genfromtxt("0.15_refractory_excited_light_restitution_200_healthy_pacemaker__100000.txt")
cells = np.zeros((np.size(filenames),200,200))
taus = np.zeros((200,200))
k=0 #dummy variable for loop 
for x in filenames:
    data = np.genfromtxt(path +x)
    for i in range (0,200):
        for j in range (0,200):
            cells[k,i,j] = data[j+200*i][0]
    plt.figure()
    plt.pcolor(cells[k])
    plt.colorbar()
    #plt.xlabel("nu")
    #plt.ylabel("P risk")
    plt.title( "Fraction of time cell spends in excited state " )
    plt.grid()
    plt.text(150, -20, r'$<\tau>=$'+str(np.round(np.average(cells[k]),4))+'$\ \sigma=$'+ str(np.round(np.std(cells[k]),4)))
    plt.savefig(x + ".png")
    plt.close()
    k+=1   
            
            
plt.figure()
plt.pcolor(cells[5])
plt.colorbar()
#plt.xlabel("nu")
#plt.ylabel("P risk")
plt.title( "Fracion of time spent in excited regime for nu = " )
plt.grid()
plt.show()              
    
    

"""
nu = np.linspace(nu_min,nu_max,num_nu)
plt.figure()
plt.pcolor(cells)
plt.colorbar()
#plt.xlabel("nu")
#plt.ylabel("P risk")
plt.title( "Fracion of time spent in excited regime for nu = " )
plt.grid()

plt.figure()
plt.pcolor(-taus)
plt.colorbar()
#plt.xlabel("nu")
#plt.ylabel("P risk")
plt.title( "<tau> distribution after 10^5 time steps" )
plt.grid()
"""




#LOOK FOR:
#average duration of episode (counter)