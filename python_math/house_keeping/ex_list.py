"""
use compression when it is helpful
"""

x = [1, 2, 3, 4]
xx = []
for ii in x :
    xx.append(ii**2)
print("\nusing a loop...")
print(f"list of elments    :  {x}")
print(f"squares of elements:  {xx}")

y = [1, 2, 3, 4]
yy = [ii**2 for ii in y]
print("\nusing compression...")
print(f"list of elments    :  {y}")
print(f"squares of elements:  {yy}")

z = [1, 2, 3, 4]
zz = [ii**2 for ii in z if ii%2 == 0]
print("\nusing compression, and a condition")
print(f"list of elments    :  {z}")
print(f"squares of elements:  {zz}")

########~~~~~~~~END>  listC.py
