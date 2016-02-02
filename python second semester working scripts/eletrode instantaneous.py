import numpy as np
import matplotlib.pyplot as plt
import os

path = "/Users/petermarinov/msci project/preferential 2/fib 2 timesteps 0.2 nu/data/"

filenames = []
for f in os.listdir(path):
    if not f.startswith('.'):
        filenames.append(f)

total = []
j1 = 100 #position of electrode
i1 = 100
k= 3
V = np.zeros((200,200))
for z in range(0,np.size(filenames),2):
    data = np.genfromtxt(path + filenames[z])
    x=0 #dummy
    for i in range (0,200):
        for j in range (0,200):
            if data[j+200*i][0] == 0:
                V[i,j] = -90.0
            if data[j+200*i][0] >1:
                V[i,j] = 20.-(110./data[j+200*i][1])*(data[j+200*i][0]-1)
            if data[j+200*i][0] ==1:
                V[i,j] = 20.
            if (i >0) and (j >0):
                x += np.float((i-i1)*(V[i,j]-V[i-1,j])+(j-j1)*(V[i,j]-V[i,j-1]))/np.float(((i-i1)**2+(j-j1)**2+k**2)**3/2)
    total.append(x)
   
   #for i in range (1,200):
        #for j in range (1,200):
            #x += np.float((i-i1)*(V[i,j]-V[i-1,j])+(j-j1)*(V[i,j]-V[i,j-1]))/np.float(((i-i1)**2+(j-j1)**2+k**2)**3/2)
   
plt.figure()    
plt.plot(total)
plt.xlabel("time [dimentionless]", fontsize = 18)
plt.ylabel("Voltage [mV]" , fontsize = 18)
plt.title("Electrode measurement obtained by simulating an eletrode and linearly interpolating a wavefront", fontsize = 10)
plt.grid()
plt.show()