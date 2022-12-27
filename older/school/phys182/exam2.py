"""
    pyhs182, exam2
"""

import math
import numpy
import os
import sys

c   = 3.0e8                                 # speed of light in a vacuum [m/s]
mu0 = 4 * numpy.pi / numpy.power(10.0, 7.0) # permeability of free space [H/m]
ep0 = 8.854e-12                             # permittivity of free space [F/m]
kb = 1.38e-23                               # regular Boltzmann constant [J/K]
kr  = 5.67e-8                               # Boltzmann radiaiton constant [J / s m^2 T^4]
h_planck = 6.626e-34                        # Planck constant, photon energy [kg m^2 / s]


def main() :
    os.system("clear")
    p1()
    p2()
    p3()
    p4()
    print("\n\n\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n")
    sys.exit()

def p1() :
   r = 0.1
   P = 150.0e3
   print(f"\n\tgiven: P = {P:0.1E} W  ,  r = {r:0.1f} m")
   A = numpy.pi * r**2
   print(f"\tthe area = pi * r^2 = {A:0.1E} m^2")
   I = P/A
   print(f"\tthe intensity = power / area = {I:0.1E} W/m^2")
   print("\tusing (I = c ep0 E^2 / 2)  ,  solve for E  ,  B = E/c")
   E = numpy.sqrt(2 * I / (c * ep0))
   B = E / c
   print(f"1a) E = {E:0.3E} V/m  ,  B = {B:0.3E} T")
   print("\n\tradiaiton pressure is reflective(it is a mirror), p = 2I/c, F = pressure * area")
   p = 2 * I / c
   F = p * A        
   print(f"1b)  F = {F:0.3E} N")
   
def p2() :
    print("\n\tf = R/2...")
    print("2ai)   at center     , f = L/2 -->   L/2 = R/2  -->  R==L")
    print("2aii)  at each mirror, f = L   -->   L = R/2    -->  R==2L")
    print("2aiii) parellel      , f = oo  -->   oo = R/2   -->  R==oo")
    f = 0.4
    n1 = 1
    n2 = 1.6
    print("\n\tnote one raidus is negative, lens maker:  1/f = (n2/n1 - 1) (1/R1 - 1/R2)")
    print("\t...R1 = |R2|, n1 = 1 ...   1/f = (n2 - 1) (2/R)")
    R = 2 * (n2 - 1) * f
    print(f"2b)    R = {R*100:0.3f} cm")

def p3() :
    lam = 1064.0e-9
    n1 = 1.0
    n2 = 1.3
    n3 = 1.5
    lmin = 4000.0e-9
    print("\n\tph1 = pi                    , low --> high, n1 < n2")
    print("\tph2 = pi + (4 pi l n2 / lam), low --> high, n2 < n3")
    print("\treflecting in constructive  , 2 pi k = ph2 - ph1   --> l = k lam / (2 n2)")
    kk = 2 * n2 * lmin / lam
    k = math.ceil(kk)
    print(f"\tk= {kk:0.3f} --> round up, k= {k}")
    l = k * lam / (2 * n2)
    print(f"3a) l = {l*1.0e9:0.1f} > lmin= {lmin*1.0e9:0.1f}, this thickness can be made")
    print("\n\tph1 = pi                   , low  --> high, n1 < n2")
    print("\tph2 = 0 + (4 pi l n2 / lam), high --> low , n2 > n3")
    print("\treflecting in constructive                , 2 pi k = ph2 - ph1   --> l = (lam/n2) (k + 1/2)")
    n22 = 1.7
    kk = (2 * n22 * lmin / lam) - (1/2)
    k = math.ceil(kk)
    l = (lam/n22) * (k + (1/2))
    print(f"\tn2= {n2}  -->  n2 = {n22}")
    print(f"\tk= {kk:0.3f} --> round up, k= {k}")
    print(f"3b) l = {l*1.0e9:0.1f} > lmin= {lmin*1.0e9:0.1f}, this thickness can be made")

def p4() :
    D = 3000.0e3
    f = 800.0
    lam = c/f
    print
    print(f"\n4a) lam= {lam:0.2E} m")
    tht = numpy.arcsin(1.22 * lam / D)
    print(f"4b) tht={tht:0.3f} rad  -->  {numpy.rad2deg(tht):0.2f} degrees")
    print("4c) increasing frequency decreases wavelength...")
    print("\tdecreasing wavelength decreases angle of resolution")


####~~~~


if __name__ == '__main__' :
    main()


########~~~~~~~~END>  exam2.py
