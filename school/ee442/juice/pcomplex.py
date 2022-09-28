"""
    given a complex number, print information
"""

import numpy as np

def pcomplex(message: str, numin: complex) -> None :
    
    print(f"{message:20} :  real=  {np.real(numin):12.3f}   ,  imag={np.imag(numin):12.3f}  ,  ", end = '')  

    print(f"abs=  {np.abs(numin):12.3f}  ,  ", end = '')
    
    print(f"angd=  {np.angle(numin, deg=True):12.3f}  ,  angr=  {np.angle(numin, deg=False):12.3f}")


########~~~~~~~~END>  pcomplex.py
