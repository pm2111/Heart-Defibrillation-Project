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
runs = 1
num_nu = np.size(filenames)
nu_min = 0.25
nu_max = .275
fibrillations = np.zeros((num_nu,runs))
fraction = np.zeros(num_nu)
for i in range (0, np.size(filenames)):
    data = np.genfromtxt(path +filenames[i])
    #np.savetxt("v2"+ filenames[i],data)
    
    
    fraction[i] = data[1]
        
    
        

nu = np.linspace(nu_min,nu_max,num_nu)
plt.plot(nu,fraction)
plt.xlabel("nu")
plt.ylabel("P risk")
plt.grid()
plt.show()