"""
    ee436, hw10, ch4, network analysis
    
    circuits operating at low frequencies and dimensions are small compared to wave length can be
    treated as an interconneciton of lumped active or passive components (phase delay is negelible)
    + everything is TEM supported by 2x conductors
    
    for microwaves, adjustments have to be made, but the concept is the same
    field analysis with Maxwell's equations will take your lunch $
    if you want to be in RF, know what tools to use for design
"""

import math
import cmath
import mpmath
import numpy
import scipy
import sympy
import os
import matplotlib.pyplot as plt

FLAG = -99.99

class Cconst() :
    c       = 3.0e8                       # speed of light in a vacuum           [m/s]
    ep0     = 8.854e-12                   # permittivity of free space           [F/m]
    mu0     = 4 * numpy.pi * 10.0e-7      # permeability of free space           [H/m]
const = Cconst()


def Npm_2_dBm(Npm) :
    """Nepers per meter --> decibels per meter"""
    dBm = Npm * (20 / numpy.log(10))
    return dBm

def dBm_2_Npm(dBm) :
    """decibels per meter --> Nepers per meter"""
    Npm = dBm * (numpy.log(10) / 20)
    return Npm

####~~~~


def main() :
    os.system("clear")
    print("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n")


####~~~~

  

    
    
####~~~~


if __name__ == '__main__' :
    main()


########~~~~~~~~END>  ch4_hw10.py
