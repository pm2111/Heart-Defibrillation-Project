import matplotlib.pylab as plt
import numpy as np
import os

#os.chdir("/Users/petermarinov/msci project/intermittent /50 hearts 10^5 nr excited 10^3 restitution 0.333 ")
path = []
path.append( "/Users/petermarinov/msci project/all code/bump experiment/50 hearts realistic linear apd tau max = 50")
path.append( "/Users/petermarinov/msci project/all code/bump experiment/50 hearts realistic linear apd tau max =75")
path.append( "/Users/petermarinov/msci project/all code/bump experiment/50 hearts realistic linear apd with bump at 67-72")
path.append( "/Users/petermarinov/msci project/all code/bump experiment/50 hearts realistic linear apd with bump at 80-85")
path.append( "/Users/petermarinov/msci project/all code/bump experiment/50 hearts realistic linear apd with bump at 89-94")
#path.append("/Users/petermarinov/msci project/all code/intermittent /50 hearts 10^5 nr excited 10^3 restitution 0.333 ")

horizontal = 100
af = np.zeros((5,8))
number_events = np.zeros((5,8))
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

number_events[0][-1] = 0    
avg_event_dur = np.divide(af,number_events)*100 #1000 timesteps inbetween each recording
avg_event_dur[0][-1] = 0
avg_event_dur[0][-2] = 0

#af = af/(np.size(data)*50.0) #normalize prob for 50 hearts
nu_shallow = np.linspace(0.14,0.22,8)
nu1 = np.linspace(0.1,0.17,8)
nu2 = np.linspace(0.12,0.19,8)
nu3 = np.linspace(0.14,0.21,8)
nu_mod = np.append(nu_shallow,np.linspace(0.8,1,4))
af1 = np.append(af,np.zeros(4))
save = np.zeros((2,8))
#save[0][:] = np.linspace(0.1,0.24,8)
#save[1][:] = af
#np.savetxt("/Users/petermarinov/msci project/all code/50 hearts restitution 0.333"+filenames[0],save)
#visualise theoretical curve
apd50 = np.genfromtxt("/Users/petermarinov/msci project/all code/50 hearts restitution 0.333/0_0.10_very light_restitution_excited_200_healthy_pacemaker_.txt")
nu = np.linspace(0.16,.24,8)
tau = 75
delta = 0.05

prisk = 1-(1-(1-nu)**tau)**(delta*L*L)
af[0][-1] = 0
plt.figure()
#plt.plot(apd50[0],apd50[1],"-o", label = "Smooth APD curve with tau max = 50 ", linewidth = 2 )
plt.plot(nu3,af[0]/(np.size(data)*50.0),"-o", label = "Smooth APD curve with tau max = 50", linewidth = 2 )
plt.plot(nu1,af[1]/(np.size(data)*50.0),"-o", label = "Smooth APD curve with tau max = 75", linewidth = 2 )
plt.plot(nu2,af[2]/(np.size(data)*43.0),"-o", label = "APD wit tau max = 50 and bump at 67-72", linewidth = 2 )
plt.plot(nu2,af[3]/(np.size(data)*43.0),"-o", label = "APD wit tau max = 50 and bump at 80-85", linewidth = 2 )
plt.plot(nu2,af[4]/(np.size(data)*43.0),"-o", label = "APD wit tau max = 50 and bump at 89-94", linewidth = 2 )
#plt.plot(nu,prisk, label = "Original Model Analytical Curve", linewidth =2)
#plt.plot(nu_pref,preferential, label = "preferential attachment structure F=10", linewidth = 2 )
#plt.plot(previous_fib[:,0],previous_fib[:,1], label = "Christensen et al.'s orignal model", linewidth = 2 )
#plt.plot(previous_fib[:,2],previous_fib[:,3], label = "Moderate APD", linewidth = 2 )
plt.xlabel(r"$\nu$", fontsize=18)
plt.ylabel("P risk", fontsize=18)
plt.legend(numpoints=1)
plt.grid()
plt.show()   

plt.figure()
#plt.plot(apd50[0],apd50[1],"-o", label = "Smooth APD curve with tau max = 50 ", linewidth = 2 )
#plt.plot(nu1,avg_event_dur[0]/(50.0),"-o", label = "Smooth APD curve with tau max = 75", linewidth = 2 )
plt.plot(nu2,avg_event_dur[1],"-o", label = "APD wit tau max = 50 and bump at 67-72", linewidth = 2 )
plt.plot(nu2,avg_event_dur[2],"-o", label = "APD wit tau max = 50 and bump at 80-85", linewidth = 2 )
plt.plot(nu2,avg_event_dur[3],"-o", label = "APD wit tau max = 50 and bump at 89-94", linewidth = 2 )
#plt.plot(nu,prisk, label = "Original Model Analytical Curve", linewidth =2)
#plt.plot(nu_pref,preferential, label = "preferential attachment structure F=10", linewidth = 2 )
#plt.plot(previous_fib[:,0],previous_fib[:,1], label = "Christensen et al.'s orignal model", linewidth = 2 )
#plt.plot(previous_fib[:,2],previous_fib[:,3], label = "Moderate APD", linewidth = 2 )
plt.xlabel(r"$\nu$", fontsize=18)
plt.ylabel("Average Event Duration", fontsize=18)
plt.legend(numpoints=1)
plt.grid()
plt.show()   