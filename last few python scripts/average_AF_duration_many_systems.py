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

horizontal = 100
af = np.zeros((6,8))
number_events = np.zeros((6,8))
L = 200 #system size
z = 0

for y in path:
    filenames = []
    for f in os.listdir(y):
     if f.endswith(".txt"):
         filenames.append('/' +f )
    j=0
    for x in filenames:
        data = np.genfromtxt(y + x)
        size = np.shape(data)
        counter=False
        for i in range (0,size[0]):
            if (data[i]>1.5*L)==True:
                af[z][j] +=1 
                counter = True
            if (data[i] >1.5*L and data[i-1] <1.5*L):
                number_events[z][j] +=1
                
        j+=1
        if j==8: #iterate through 8 nus 
            j=0
    z+=1

  
avg_event_dur = np.divide(af,number_events)*100 #1000 timesteps inbetween each recording
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
    plt.plot(nus[i],avg_event_dur[i],"-o", label = lab[i], linewidth =2)
#plt.plot(previous_fib[:,0],previous_fib[:,1], label = "Christensen et al.'s Original Model")
#plt.plot(nu_pref,preferential, label = "preferential attachment structure F=10", linewidth = 2 )
#plt.plot(previous_fib[:,0],previous_fib[:,1], label = "Christensen et al.'s orignal model", linewidth = 2 )
#plt.plot(previous_fib[:,2],previous_fib[:,3], label = "Moderate APD", linewidth = 2 )
plt.xlabel(r"$\nu$", fontsize=18)
plt.ylabel("Average Event Duration [simulation timesteps]", fontsize=18)
#plt.title( "Intermittent AF comparison between models for 50 randomly seeded hearts" ,fontsize=12)
plt.legend()
plt.grid()
plt.show()   
