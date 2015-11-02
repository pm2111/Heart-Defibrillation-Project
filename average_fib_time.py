import numpy as np
import matplotlib.pyplot as plt
import os

horizontal = 100

path = "/Users/petermarinov/msci project/msci project computation night1/curve/data/"

filenames = os.listdir(path)

runs = 3
num_nu = 7
nu_min = 0.21
nu_max = .24
fibrillations = np.zeros((num_nu,runs))
fraction = np.zeros((num_nu,runs))
for j in range(0,runs): 
    for i in range(0,num_nu):
        time = 0
        data = np.genfromtxt(path +filenames[i+j*num_nu])
        #np.savetxt("v2"+ filenames[i],data)
        
        for x in data:
            if x >1.5*horizontal:
                time +=1
        fibrillations[i][j] = time
        fraction[i][j] = np.divide(fibrillations[i][j],data.size)
    
    
averaged = np.average(fraction,1)
        

nu = np.linspace(nu_min,nu_max,7)
plt.plot(nu,averaged)
plt.xlabel("nu")
plt.ylabel("P risk")
plt.grid()
plt.show()