"""
    hw11, v3, ch6, photons
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

class tab_1 :
    color = ["violet", "blue", "green", "yellow", "yellow"]
    table = numpy.array([
        [4.047e-7, 18.6, 11.9, 14.18, 16.52e-7],
        [4.916e-7, 20.6, 14.4, 17.30, 16.53e-7],
        [5.461e-7, 22.6, 16.4, 19.30, 16.52e-7],
        [5.770e-7, 23.6, 17.4, 20.45, 16.51e-7],
        [5.790e-7, 23.7, 17.5, 20.52, 16.52e-7]
    ], dtype=float)
    def __init__(self) :
        self.dbar = 16.52
        self.alpha = 0.003
        self.sig = 0
    def tset(self) :
        self.dbar = 0
        self.sig = 0
        for row in self.table :
            row[3] = row[1] - row[2]
            row[4] = row[0] / numpy.sin(numpy.deg2rad(row[3]))
            self.dbar = self.dbar + row[4]
        self.dbar = self.dbar / 6
        temp = 0
        for row in self.table :
            temp = temp + (row[4] - self.dbar)**2
        self.sig = numpy.sqrt((1/5) * temp)
        self.alpha = self.sig / numpy.sqrt(5-1)
    def tprint(self) :
        print("\ntable 1:\n\n")
        print("color    |  lam/10^7 | thtR  | thtL   | tht  | d/10^7")
        print("-----------------------------------------------------")
        cnt=0
        for row in self.table :
            print(f"{self.color[cnt]:7}  | ", end='')
            print(f"{row[0]*1.0e7:0.3f}     |", end='')
            print(f"{row[1]:0.1f}    | ", end='')
            print(f"{row[2]:0.1f}    |", end='')
            print(f"{row[3]:0.1f}    | ", end='')
            print(f"{row[4]*1.0e7:0.2f}")
            cnt=cnt+1
        print(f"dbar = {self.dbar*1.0e7:0.2f}")
        print(f"alpha {self.alpha:0.4f}")
        print(f"with {cnt} measuremts, std= {self.sig}")

class tab_2 :
    color = ["violet", "blue", "blueg", "red"]
    t_a = numpy.array([
        [4.102/1.0e-7, 6, 9],
    ])

def main() :
    os.system("clear")
    #prelab()
    plotter()
    #t1 = tab_1()
    #t1.tset()
    #t1.tprint()

    print("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n")

def prelab() :
    print("\n#2)")
    for n in range(3,7) :
        lam = 1/(const.RH * ((1/4) - (1/n**2)))
        print(f"n={n}, lam= {lam*1.0e9:0.1f} nm")
    print("\n#6)")
    rh = const.mass_e * const.eV**4 / (8 * const.ep0**2 * const.c * const.h**3)
    print(f"RH= {rh:0.3E}  1/m")
    print("\n7)")
    d = 1.5e-6
    lam = 5.555e-7
    tht = numpy.arcsin(lam/d)
    print(f"tht= {tht:0.3f} rad -->  {numpy.rad2deg(tht):0.2f} deg")

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


########~~~~~~~~END>  lab43.py
