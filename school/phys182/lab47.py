"""
    lab#45
"""

import math
import cmath
from matplotlib import pyplot as plt
import mpmath
import numpy
import scipy
import sympy
import os

class Cconst() :
    c       = 3.0e8                                      # speed of light in a vacuum                [m/s]
    E0      = 2.17e-18                                   # ground state energy (ionize limit)        [J]
    ep0     = 8.854e-12                                  # permittivity of free space                [F/m]
    eV      = 1.6e-19                                    # electron volt, energy for electron +1V    [J] ...close fundamental coulumbs
    h       = 6.626e-34                                  # Planck constant, photon energy            [kg m^2 / s]  ...hbar = h / (2 pi)
    kb      = 1.38e-23                                   # regular Boltzmann constant                [J/K]
    kr      = 5.67e-8                                    # Boltzmann radiaiton constant              [J / s m^2 T^4]
    lamC    = 2.43e-12                                   # h/(m0 c) == Compton wavelength            [m]
    lmaxT   = 2.898e-3                                   # relates peak wave length and temperature  [m K]
    mass_e  = 9.109e-31                                  # mass of electron                          [kg]
    mass_n  = 1.675e-27                                  # mass of neutron                           [kg]  
    mass_p  = 1.673e-27                                  # mass of a proton                          [kg]  ?
    mu0     = 4 * numpy.pi / numpy.power(10.0, 7.0)      # permeability of free space                [H/m]
    rbhor   = 5.292e-11                                  # Bhor radius, a0                           [m]
    RH      = 1.097e7                                    # Ryberg constant                           [1/m]
const = Cconst()

data1 = numpy.array([
        [0  , 0,    0,    0   ],
        [425, 1882, 1835, 1859],
        [450, 3067, 3094, 3103],
        [500, 3264, 3168, 3119],
        [550, 3519, 3486, 3523],
        [600, 3712, 3750, 3767],
        [650, 4120, 3977, 4065],
        [700, 5041, 4753, 4994]
    ], dtype=numpy.float32)
calc1 = numpy.zeros((8,3), dtype=numpy.float32)

data2 = numpy.array([5679, 5013, 4521, 3860, 3595, 3082, 2782, 2482, 2171, 1823, 1536, 1286, 1071], dtype=numpy.float32)
calc2 = numpy.zeros((8,3), dtype=numpy.float32)

def main() :
    os.system("clear")

    for ii in range(0, 8) :
        avg = (1/3) * (data1[ii][1] + data1[ii][2] + data1[ii][3])
        calc1[ii][0] = avg
        calc1[ii][1] = getalp(avg, [data1[ii][1], data1[ii][2], data1[ii][3]])
        calc1[ii][2] = numpy.sqrt(avg)
    print("\nCbar |  alpha | sqrt(Cbar)")
    print("-----------------------------")
    alpc = 0
    sqc = 0
    for ii in range(0, 8) :
        print(f"{calc1[ii][0]:7.1f} | {calc1[ii][1]:7.1f} | {calc1[ii][2]:7.1f}")
        alpc += calc1[ii][1]
        sqc += calc1[ii][2]
    print(f"alpc= {alpc/8:0.1f}  ,  sqc= {sqc/8:0.1f}")



    print("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n")

def getalp(avg, stuff) :
    temp = 0
    for ii in stuff :
        temp = temp + (ii - avg)**2
    sig = numpy.sqrt((1/2) * temp)
    return (sig/numpy.sqrt(3))

def plotter() :
    d = 1.616e-7
    xx = numpy.array([2.426e6, 2.0233e6, 1.505e6])
    yy = numpy.array([(1/4) - (1/36), (1/4) - (1/16), (1/4) - (1/9)])
    datap = xx.size

    a = datap * numpy.dot(xx, yy)
    b = numpy.sum(xx) * numpy.sum(yy)
    c = datap * numpy.dot(xx,xx)
    d = numpy.sum(xx)**2
    m = (a - b) / (c - d)

    f = numpy.sum(yy) * numpy.dot(xx,xx)
    g = numpy.dot(xx,yy) * numpy.sum(xx)
    h = datap * numpy.dot(xx,xx) - numpy.sum(xx)**2
    b = (f - g) / h

    print(f"\nm= {m:0.3E}")
    print(f"b = {b:0.3E}")
    print(f"y = [{m:0.3E}] x + {b:0.3E}")

    mxx = numpy.linspace(0.1, 0.3, 50)
    myy = []
    for idx in range(0, 50) :
        myy.append(mxx[idx] * m + b)
        print(f"mxx[{idx}]= {mxx[idx]:0.3E}  ,  myy[{idx}]= {myy[idx]:0.3E}")

    plt.title("Hydrogen Spectrum") 
    plt.xlabel("1/4 - 1/n^2") 
    plt.ylabel("1/lam") 
    plt.plot(xx,yy,"ob") 
    plt.plot(mxx,myy, "r-")
    plt.show() 

####~~~~


if __name__ == '__main__' :
    main()


########~~~~~~~~END>  lab47.py
