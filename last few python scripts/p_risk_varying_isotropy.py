import matplotlib.pylab as plt
import numpy as np
import os

#os.chdir("/Users/petermarinov/msci project/intermittent /50 hearts 10^5 nr excited 10^3 restitution 0.333 ")
path = []
path.append( "/Users/petermarinov/msci project/all code/50 hearts preferential/50 hearts anis 0.5 corr 0.2/50 hearts 0.333 restitution")
path.append( "/Users/petermarinov/msci project/all code/50 hearts preferential/50 hearts anis 0.5 corr 0.5/50 hearts 0.333 restitution")
path.append( "/Users/petermarinov/msci project/all code/50 hearts preferential/50 hearts anis -0.5 corr 0.99/50 hearts 0.333 restitution")
path.append( "/Users/petermarinov/msci project/all code/50 hearts preferential/50 hearts anis 0.2 corr 0.99/50 hearts 0.333 restitution")
path.append( "/Users/petermarinov/msci project/all code/50 hearts preferential/50 hearts anis 0.5 corr 0.99/50 hearts 0.333 restitution")
path.append( "/Users/petermarinov/msci project/all code/50 hearts preferential/50 hearts anis 0.99 corr 0.99/50 hearts 0.333 restitution")
previous_fib = np.genfromtxt("/Users/petermarinov/msci project/all code/intermittent /paroxysmal.txt") #1 for christensen, 2 for 1d corr
lab = ["anis = 0.5 corr = 0.2","anis = 0.5 corr = 0.5","anis = -0.5 corr = 0.99","anis = 0.2 corr = 0.99","anis = 0.5 corr = 0.99","anis = 0.99 corr = 0.99"]

k=0
paroxysmal = np.zeros((6,8))
for z in path:
    filenames = []
    for f in os.listdir(z):
     if f.endswith(".txt"):
         filenames.append('/' +f )
    L = 200 #system size
    j=0
    for x in filenames:
        data = np.genfromtxt(z + x)
        size = np.shape(data)
        paroxysmal_count=0
        counter=False
        for i in range (0,size[0]):
            if counter and (data[i]>1.5*L)==False:
                paroxysmal[k][j] +=1 
            if (data[i]>1.5*L):
                counter=True
            else:
                counter=False
                
        j+=1
        if j==8: #iterate through 8 nus 
            j=0
    k+=1

nus = []        
nus.append(np.linspace(0.10,0.38,8))
nus.append(np.linspace(0.20,0.48,8))
nus.append(np.linspace(0.40,0.68,8))
nus.append(np.linspace(0.40,0.68,8))
nus.append(np.linspace(0.40,0.68,8))
nus.append(np.linspace(0.60,0.88,8))



previous_fib = np.genfromtxt("/Users/petermarinov/msci project/all code/intermittent /paroxysmal.txt")
preferential = [196,214,250,564,734,149,31,0,0,0,0,0]
nu_pref = np.linspace(0.15,0.7,12)

plt.figure()
for i in range (0,6):
    plt.plot(nus[i],paroxysmal[i], label = lab[i], linewidth =2)
#plt.plot(previous_fib[:,0],previous_fib[:,1], label = "Christensen et al.'s Original Model")
#plt.plot(nu_pref,preferential, label = "preferential attachment structure F=10", linewidth = 2 )
#plt.plot(previous_fib[:,0],previous_fib[:,1], label = "Christensen et al.'s orignal model", linewidth = 2 )
#plt.plot(previous_fib[:,2],previous_fib[:,3], label = "Moderate APD", linewidth = 2 )
plt.xlabel(r"$\nu$", fontsize=18)
plt.ylabel("intermittent fibrillation count", fontsize=18)
plt.title( "Intermittent AF comparison between models for 50 randomly seeded hearts" ,fontsize=12)
plt.legend()
plt.grid()
plt.show()   
