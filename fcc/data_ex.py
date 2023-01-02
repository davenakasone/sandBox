"""
    see what data type makes the most sense for your application
"""

import numpy as np
import os
import sys
from timeit import default_timer as timer

os.system("clear")
arrSize = 99999999

x = list(range(arrSize))
print(type(x))
print(f"element bytes: {sys.getsizeof(x[0])}")
print(f"total bytes: {sys.getsizeof(x)}\n")

xx = np.arange(arrSize)
print(type(xx))
print(f"element bytes: {sys.getsizeof(xx[0])}")
print(f"total bytes: {sys.getsizeof(xx)}")

print("\nthe python list: ", end='')
start = timer()
temp = sum([i ** 2 for i in x])
end = timer()
print(f"{end - start} seconds")

print("\nthe numpy array: ", end='')
start = timer()
temp = np.sum(xx ** 2)
end = timer()
print(f"{end - start} seconds")

print("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n")
sys.exit()


####~~~~END>  data_ex.py