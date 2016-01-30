import numpy as np
import matplotlib.pyplot as plt
import os

path = "/Users/petermarinov/msci project/electrode data/test data/data/"

filenames = []
for f in os.listdir(path):
    if not f.startswith('.'):
        filenames.append(f)

i=-12

data = np.genfromtxt(path + filenames[i])
V = np.zeros((200,200))
for i in range (0,200):
    for j in range (0,200):
        if data[j+200*i][0] == 0:
            V[i,j] = -90.0
        if data[j+200*i][0] >1:
            V[i,j] = 20.-(110./data[j+200*i][1])*(data[j+200*i][0]-1)
        if data[j+200*i][0] ==1:
            V[i,j] = 20.


i1 = 50
k= 3
total = []
x=0 #dummy
elec = np.zeros((200,200,200))
for j1 in range(0,200):
    for i in range (1,200):
        for j in range (1,200):
            #elec[j1,i,j] = np.divide(float((i-i1)*(V[i,j]-V[i-1,j])+(j-j1)*(V[i,j]-V[i,j-1])),float(((i-i1)**2+ (j-j1)**2 +k**2)**(3/2)))
            #x +=((i-i1)*(V[i,j]-V[i-1,j])+(j-j1)*(V[i,j]-V[i,j-1]))/((i-i1)**2+ (j-j1)**2 +k**2)**(3/2)
            x += np.float((i-i1)*(V[i,j]-V[i-1,j])+(j-j1)*(V[i,j]-V[i,j-1]))/np.float(((i-i1)**2+(j-j1)**2+k**2)**3/2)
    total.append(x)                                         
    x=0
    
plt.plot(total)
plt.xlabel("time [dimentionless]", fontsize = 18)
plt.ylabel("Voltage [mV]" , fontsize = 18)
plt.title("Electrode measurement for a healthy pacing heart")
plt.grid()
plt.show()