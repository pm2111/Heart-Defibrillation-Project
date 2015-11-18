import numpy as np
import matplotlib.pyplot as plt
import os

path = "/Users/petermarinov/msci project/msci project computation night1/results james/"
filenames = []

for f in os.listdir(path):
    if not f.startswith('.'):
        filenames.append(f)

horizontal = 100


# = os.listdir(path)
runs = 3
num_nu = np.size(filenames)/runs
nu_min = 0.25
nu_max = .275
fibrillations = np.zeros((num_nu,runs))
fraction = np.zeros((num_nu,runs))
for j in range(0,runs): 
    for i in range(0,num_nu):
        time = 0
        data = np.genfromtxt(path +filenames[i])
        #np.savetxt("v2"+ filenames[i],data)
        
        fraction[i] = data[1]
    
    
averaged = np.average(fraction,1)
        

nu = np.linspace(nu_min,nu_max,num_nu)
plt.plot(nu,averaged)
plt.xlabel("nu")
plt.ylabel("P risk")
plt.grid()
plt.show()