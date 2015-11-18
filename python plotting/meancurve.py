import numpy as np
import matplotlib.pyplot as plt
import os

horizontal = 100

loc = "/Users/petermarinov/msci project/msci project computation night1/change name/"

filenames = os.listdir(loc)

total = np.zeros(np.size(filenames))
for i in range(0,np.size(filenames)):
    time = 0
    data = np.genfromtxt(loc+filenames[i])
    np.savetxt("v13"+ filenames[i],data)
    




#nu = np.linspace(0.23,.28,np.size(filenames))
#plt.plot(nu,fraction)
