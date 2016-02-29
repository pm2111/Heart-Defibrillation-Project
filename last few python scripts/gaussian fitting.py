import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt
import os

path = "/Users/petermarinov/msci project/all code/50 hearts preferential/50 hearts anis 0.99 corr 0.99/50 hearts 0.333 restitution"
previous_fib = np.genfromtxt("/Users/petermarinov/msci project/all code/intermittent /paroxysmal.txt") #chrsitensen s original model at [1] 

# Define some test data which is close to Gaussian

k=0
paroxysmal = np.zeros(8)

filenames = []
for f in os.listdir(path):
    if f.endswith(".txt"):
        filenames.append('/' +f )
L = 200 #system size
j=0
for x in filenames:
    data = np.genfromtxt(path + x)
    size = np.shape(data)
    paroxysmal_count=0
    counter=False
    for i in range (0,size[0]):
        if counter and (data[i]>1.5*L)==False:
            paroxysmal[j] +=1 
        if (data[i]>1.5*L):
            counter=True
        else:
            counter=False
            
    j+=1
    if j==8: #iterate through 8 nus 
        j=0
k+=1

p0 = [1., 0., 1.]
# Define model function to be used to fit to the data above:
def gauss(x, *p):
    A, mu, sigma = p
    return A*np.exp(-(x-mu)**2/(2.*sigma**2))
    
nus =np.linspace(0.60,0.88,8)
coeff, var_matrix = curve_fit(gauss, nus, paroxysmal, p0 =p0)
#get fitted curve
fitted = gauss(nus, *coeff)

plt.figure()
plt.grid()
plt.plot(nus,fitted,linewidth= 2, label = "Gaussian Fit")
plt.plot(nus,paroxysmal,"o", linewidth =2,label = "Paroxysmal Data Points" )
plt.legend(numpoints =1)
plt.xlabel(r"$\nu$",fontsize =20)
plt.ylabel( "Number of Episodes", fontsize = 20 )
plt.text(nus[-1]-0.07, coeff[0]-100, r'A=' +str(np.round(coeff[0],2))+" $<\mu>=$" +str(np.round(coeff[1],2))+' $\ \sigma=$'+ str(np.round(coeff[2],2)),fontsize = 15)
plt.show()