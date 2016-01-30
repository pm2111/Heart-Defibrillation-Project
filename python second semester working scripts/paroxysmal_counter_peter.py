import matplotlib.pylab as plt
import numpy as np
import os

os.chdir("/Users/petermarinov/msci project/intermittent /50 hearts 10^5 nr excited 10^3 restitution 0.333 ")
path = "/Users/petermarinov/msci project/intermittent /50 hearts 10^5 nr excited 10^3 restitution 0.333 "
filenames = []

for f in os.listdir(os.getcwd()):
     if f.endswith(".txt") and f.find("average")==-1:
         filenames.append('/' +f )

risk_curve = np.zeros((len(filenames),3))
horizontal = 100
paroxysmal = np.zeros(8)
L = 200 #system size

j=0
for x in filenames:
    data = np.genfromtxt(path + x)
    size = np.shape(data)
    paroxysmal_count=0
    counter=False
    for i in range (0,size[0]):
        if counter and (data[i][1]>1.5*L)==False:
            paroxysmal[j] +=1 
        if (data[i][1]>1.5*L):
            counter=True
        else:
            counter=False
            
    j+=1
    if j==8: #iterate through 8 nus 
        j=0

nu_shallow = np.linspace(0.10,0.24,8)
previous_fib = np.genfromtxt("/Users/petermarinov/msci project/intermittent /paroxysmal.txt")
preferential = [196,214,250,564,734,149,31,0,0,0,0,0]
nu_pref = np.linspace(0.15,0.7,12)

plt.figure()

plt.plot(nu_shallow,paroxysmal, label = "shallow apd function", linewidth = 2 )
plt.plot(nu_pref,preferential, label = "preferential attachment structure F=10", linewidth = 2 )
plt.plot(previous_fib[:,0],previous_fib[:,1], label = "Christensen et al.'s orignal model", linewidth = 2 )
plt.plot(previous_fib[:,2],previous_fib[:,3], label = "Moderate APD", linewidth = 2 )
plt.xlabel(r"$\nu$", fontsize=18)
plt.ylabel("intermittent fibrillation count", fontsize=18)
plt.title( "Intermittent AF comparison between models for 50 randomly seeded hearts" ,fontsize=12)
plt.legend()
plt.grid()
plt.show()   
