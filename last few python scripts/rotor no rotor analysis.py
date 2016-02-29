import numpy as np
import matplotlib.pyplot as plt
import os
from scipy import signal

path = "/Users/petermarinov/msci project/all code/ecg rotor no rotor/rotor data more than 800 excited cells/"

filenames = []

for f in os.listdir(path):
    if not f.startswith('.'):
        if f.endswith("txt"):
            filenames.append(f)

horizontal = 100

lab = ["electrode on top of vortex","distant electrode"]

total = np.zeros((200,200))
k=0 #dummy variable for loop 

for i in [1]:
    data = np.genfromtxt(path + filenames[-3])
    #plt.plot(data[13640:14640,0],data[13640:14640,i], label = lab[i-1])
    #plt.plot(data[13640:17640,0],data[13640:17640,i], label = lab[i-1])
    plt.plot(data[:,0],data[:,i], label = lab[i-1])
    plt.grid()
    plt.legend()
    plt.xlabel("simulation time")
    plt.ylabel("Voltage [mV]")

#estimate the number of potential electrogram cycles n
#overestimate better than underestimate
a = data[:150,1]
n = 20
ind = np.argpartition(a, -n)[-n:]
ind.sort()
ind = np.append(ind,ind[-1] *10)
maxima = []
#make sure we haven't picked 2 points of the same maxima 
for i in range (0,n):
    if abs(ind[i+1]- ind[i]) >20:
        maxima.append(ind[i])
        #maxima.append(ind[i+1])
        k = i
        z = i
        while (abs(ind[k]- ind[k-1])< 5):
            if data[ind[k-1]][1] > data[ind[z]][1]:
                maxima[-1] = ind[k-1]
                z = k-1
            k -=1
            if k == n-1:
                break
                    
print maxima
