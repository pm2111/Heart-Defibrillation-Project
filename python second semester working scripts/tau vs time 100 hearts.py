import numpy as np
import matplotlib.pyplot as plt
import os

path = "/Users/petermarinov/msci project/preferential 1/100 hearts tau F10/data/"
number_nus = 8

filenames = []
for f in os.listdir(path):
    if not f.startswith('.'):
        filenames.append(f)

filenames = np.sort(filenames)
total_time = 1000. 

total = np.zeros((100,number_nus))


k=0 #dummy variable for loop 
j=0
non_zero =np.zeros(8)
for j in range (0,8):
    for x in filenames[j::number_nus]:
        data = np.genfromtxt(path +x)
        if data[:,1].mean() <50:
            total[:,j] += data[:,1]
            non_zero[j] +=1
        if data[:,1].mean()==50:
            print j
       
            
  
legend = ["0.15 nu ",  "0.1 nu", "0.25 nu", "0.20 nu", "0.35 nu" , "0.3 nu", "0.45 nu" ,"0.4 nu" ]
plt.figure()
y=[]
yerr =[]
for i in [1,0,3,2,5,4,7]:
    plt.plot(np.linspace(0,99000,100),total[:,i]/non_zero[i], label = legend[i], linewidth = 2 )
    y.append(total[-1,i]/non_zero[i])
    yerr.append(np.std(total[:,i]/non_zero[i]))
plt.xlabel("time [dimentionless]")
plt.ylabel(r"$ <\tau> $ [dimentionless]", fontsize=18)
plt.title( "Average refractory period vs.simulation time" ,fontsize=18)
plt.legend()
plt.grid()
plt.show()      

plt.figure()
plt.grid()
plt.errorbar(np.linspace(0.1,0.4,7),y, yerr = yerr,fmt="o")
plt.xlabel(r"$\nu$", fontsize = 18)
plt.ylabel(r"$<\tau>_{steady}$", fontsize = 18)
plt.axis([0, 0.45, 35, 52])
plt.show()