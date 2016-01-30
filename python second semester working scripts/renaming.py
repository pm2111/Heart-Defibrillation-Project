__author__ = 'James'
import numpy as np
import os

os.chdir("/Users/petermarinov/msci project/intermittent /50 hearts 10^5 nr excited 10^3 restitution 0.333 ")

filenames = []

for filename in os.listdir(os.getcwd()):
      if filename[6] == "_":
          str1 = filename[:6]
          str2 = filename[6:]
          tot = str1 + "0" + str2
          os.rename(filename, tot)
        
            
            
            
