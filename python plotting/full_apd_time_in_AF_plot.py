import numpy as np
import matplotlib.pyplot as plt
import os

path = "0.17_restitution_200_healthy_pacemaker__100000.txt"


filenames = []

for f in os.listdir(os.getcwd()):
    if not f.startswith('.'):
        filenames.append( "/" + f )

horizontal = 100
L = 200 #system size
total_time = 100000.
# = os.listdir(path)
runs = 4
num_nu = np.size(filenames)/runs
nu_min = 0.1
nu_max = .22

fraction = np.zeros((num_nu,runs))

cells = np.zeros((200,200))


j = 0
fib_time = np.zeros(np.size(filenames))
full = np.zeros((2,40))

data = np.genfromtxt(os.getcwd()+"/average_time_in_af.txt")
data1 = np.genfromtxt(os.getcwd()+"/average_time_in_af_res1.txt")
"""np.insert(data,0,np.zeros(8))
np.insert(data,-1,np.zeros(8))
np.insert(data1,0,np.zeros(8))
np.insert(data1,-1,np.zeros(8))"""


np.append(data,np.zeros(3))    
    
    
       
    

    


nu = np.linspace(.09,.22,13)
plt.figure()
plt.plot(data,"o",label = "no restitution")
plt.plot(data1,"o", label = "moderate restitution")
plt.legend()
plt.xlabel("nu")
plt.ylabel("average duration of AF")
#plt.title( "Fracion of time spent in excited regime for nu = " )
plt.grid()
plt.show()
#LOOK FOR:
#average duration of episode (counter)
#P risk: add column and divide by time (length of array)"""
