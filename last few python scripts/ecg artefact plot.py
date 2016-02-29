import numpy as np
import matplotlib.pyplot as plt
import os
from scipy import signal

path = "/Users/petermarinov/msci project/all code/electrode data/artefact/data/"

filenames = []

for f in os.listdir(path):
    if not f.startswith('.'):
        if f.endswith("txt"):
            filenames.append(f)

horizontal = 100
L = 200
lab = ["electrode on top of vortex","distant electrode"]

total = np.zeros((200,200))
k=0 #dummy variable for loop 
y = []
xs = []
i = 0
for x in filenames:
    data = np.genfromtxt(path + x)
    #plt.plot(data[13640:14640,0],data[13640:14640,i], label = lab[i-1])
    #plt.plot(data[13640:17640,0],data[13640:17640,i], label = lab[i-1])
    y.append(data[L+10*i,1])
    xs.append(L+i*10)
    i +=1
plt.show()
    
#amplitude of crest calculation:
plt.figure()
plt.plot(xs,y)
plt.grid()
plt.legend()
plt.xlabel("System Size L")
plt.ylabel("Artefact Voltage [mV]")
plt.show()