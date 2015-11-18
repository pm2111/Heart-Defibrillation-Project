import numpy as np
import matplotlib.pyplot as plt
import os

path = "/Users/petermarinov/msci project/msci project computation night1/results james 1/"
filenames = []

for f in os.listdir(path):
    if not f.startswith('.'):
        filenames.append(f)

horizontal = 100


# = os.listdir(path)
runs = 4
num_nu = np.size(filenames)/runs
nu_min = 0.21
nu_max = .34
fraction = np.zeros((num_nu,runs))
for j in range(0,runs):  
    for i in range(0,num_nu):
        time = 0
        data = np.genfromtxt(path +filenames[i+j*num_nu])
        
        
        fraction[i][j] = data[1]
    
    
averaged = np.average(fraction,1)
std = 0.0      
for j in range(0,runs):  
    for i in range(0,num_nu): 
        std += abs((fraction[i][j]-averaged[i]))
        print std

nu = np.linspace(nu_min,nu_max,num_nu)
plt.figure()
plt.errorbar(nu,averaged, yerr= 0.143)
plt.xlabel("nu")
plt.ylabel("P risk")
plt.grid()
plt.show()
#LOOK FOR:
#average duration of episode (counter)
#P risk: add column and divide by time (length of array)


