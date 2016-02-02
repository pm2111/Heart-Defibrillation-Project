__author__ = 'James'
import numpy as np
import os

os.chdir("/Users/petermarinov/msci project/preferential 2/fib 2 timesteps 0.2 nu/data/")

filenames = []

for filename in os.listdir(os.getcwd()):
      if filename[7] == "_":
          str1 = filename[:7]
          str2 = filename[7:]
          tot = str1 + "00" + str2
          os.rename(filename, tot)
      if filename[8] == "_":
          str1 = filename[:8]
          str2 = filename[8:]
          tot = str1 + "0" + str2
          os.rename(filename, tot)
        
            
            
            
