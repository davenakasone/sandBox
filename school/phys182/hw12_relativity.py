"""
    hw12, v3, ch5, relativity
"""

import math
import cmath
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
    
const = Cconst()

def lorentz(v: float) -> float :
    return (1 / numpy.sqrt(1 - (v**2/const.c**2)))

                             
def main() :
    os.system("clear")
    #p1()
    #p2()
    #p3()
    #p4()
    #p5()
    #p6()
    #p7()
    #p8()
    #p9()
    #p10()
    #p11()
    #p12() 
    #p13()
    #p14()
    p15()
    print("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n")

def p1() :
    print("\nproblem # 1")
    p = 0.045
    G = 1 + p
    vc = numpy.sqrt(1 - (1/(G**2)))
    print(f"a) v/c = {vc:0.4f}")
    
def p2() :
    print("\nproblem # 2")
    v = 0.765 * const.c
    t = 1.175e-8
    G = lorentz(v)
    dt = t * G
    print(f"a) dt= {dt:0.3E}")
    
def p3() :
    print("\nproblem # 3")
    G = 1.01
    vc = numpy.sqrt(1 - (1/G)**2)
    print(f"a) v/c= {vc:0.3f}")
    
def p4() :
    print("\nproblem # 4")
    v = 0.89 * const.c
    t = 1.4e-6
    G = lorentz(v)
    L0 = v * t * G
    print(f"a) L0 =  {L0/1.0e3:0.4} km")
    L = v * t
    print(f"b) L  = {L/1.0e3:0.4f} km")
    
def p5 () :
    print("\nproblem # 5")
    L = 91 * 0.9144       # yd --> m
    L0 = 100              # meters
    rat = L / L0
    vc = numpy.sqrt(1 - rat**2)
    print(f"vc= {vc:0.4f}")
    
def p6() :
    print("\nproblem # 6")
    v1 = 0.75 
    v2 = 0.55
    uc = (v2 - v1) / (1 - (v1 * v2))
    print(f"a) uc = {uc:0.4f}")
    ucc = -1 * (v1 + v2) / (1 + (v1 * v2))
    print(f"b) ucc= {ucc:0.4f}")
    
def p7() :
    print("\nproblem # 7")
    u1 = 0.735
    u2 = 0.955
    vc = (u1 - u2) / (1 - (u1 * u2))
    print(f"vc = {vc:0.4f}")
    
def p8() :
    print("\nproblem # 8")
    lam = 1891e-9
    lam0 = 1875e-9
    num = (lam/lam0)**2 - 1
    den = (lam/lam0)**2 + 1
    uc = num/den
    print(f"uc= {uc:0.5f}")

def p9() :
    print("\nproblem # 9")
    v = 0.31 * const.c
    m = 6.645e-27
    G = lorentz(v)
    p = m * v * G
    print(f"p= {p:0.4E}")
    
    
def p10() :
    print("\nproblem # 10")
    m = 9.109e-31
    v1 = 27
    p1 = m * v1
    print(f"a) p1=  {p1:0.3E}    kg m / s")
    v2 = 0.14 * const.c
    G2 = lorentz(v2)
    p2 = m * v2 * G2
    print(f"b) p2=  {p2:0.3E}    kg m / s")
    v3 = 0.84 * const.c
    G3 = lorentz(v3)
    p3 = m * v3 * G3
    print(f"c) p3=  {p3:0.3E}    kg m / s")
    p33 = p3 / G3
    print(f"d) p33=  {p33:0.3E}    kg m / s")
    print(f"e) p/pclass=  {p3/p33:0.4f}")
    print("f)")
    print("    does not depend on mass of electron")
    print("    approaches oo as v->c")
    G = lorentz(0.997*const.c)
    print(f"g) rat= {G:0.3f}")
    
def p11() :
    print("\nproblem # 11")
    p = 1
    c = 2.998e8
    m = 1.673e-27
    G = numpy.sqrt(1 + (p / (m * c)**2))
    print(f"a) G= {G:0.3E}")
    u = c * numpy.sqrt(1 - (1/G**2))
    print(f"b) u = {u:0.4E}")
    
def p12() :
    print("\nproblem # 12")
    m = 1.67e-27
    E0 = m * const.c**2
    print(f"a) E0 = {E0:0.3E} J")
    print(f"b) E0 = {E0/(1.6e-13):0.3f} MeV")
    
def p13() :
    print("\nproblem # 13")
    m = 1.05e31
    E = 1.8e44
    dm = E / const.c**2
    print(f"a) dm=  {dm:0.3E}")
    ratm = dm / m
    print(f"b) dm/m=  {ratm:0.5f}")
    
def p14() :
    print("\nproblem # 14")
    mf = 1.05
    m = 1
    E = 8.0e13
    dm = mf * E / const.c**2
    print(f"a) dm=  {dm*1.0e3:0.3f} g")
    rat = dm / mf
    print(f"b) dm/m = {rat:0.3E}")
    
def p15() :
    print("\nproblem # 15")
    ke = 0.85 * 1.60e-13# MeV -> J
    m = 9.11e-31
    c = 3.0e8
    
    aa = ke / (m * c**2)
    bb = (1 + aa)**2
    tempC = 1 - (1 / bb)
    vc = numpy.sqrt(tempC)
    print(f"v/c=  {vc:0.4f}")
    


####~~~~


if __name__ == '__main__' :
    main()


########~~~~~~~~END>  hw12_relativity.py
