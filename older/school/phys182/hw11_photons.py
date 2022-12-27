"""
    hw11, v3, ch6, photons
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
    p13()
    print("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n")

def p1() :
    print("\nproblem # 1")
    f = 1.4e13
    dE = const.h * f / const.eV
    print(f"1a) dE = hf = {dE:0.4f} eV")
    E = 1.5 # eV
    n = (E/(const.h * f / const.eV)) - (1/2)
    print(f"1b) n = {n}  -->  {round(n)}")
    
def p2() :
    print("\nproblem # 2")
    lpeak = 580.0e-9
    Tb = 1100.0 # K
    T = const.lmaxT / lpeak
    print(f"2a) T = {T:0.3f} K")
    lam = const.lmaxT / Tb
    print(f"2b) lam = {lam*1.0e9:0.3f} nm")
    
def p3() :
    print("\nproblem # 3")
    lam = 360.0e-9
    EK = 0.81 # eV, kinetic enegery
    BE = ((const.h * const.c / const.eV) / lam) - EK
    print(f"3) BE = {BE:0.3f} eV")
    
def p4() :
    print("\nproblem # 4")
    wfun = 1.1 # eV, work function
    lam0 = 400.0e-9
    lam1 = 700e-9
    Ei = (const.h * const.c / lam0) / const.eV
    KEmax = Ei - wfun
    print(f"4) KEmax = {KEmax:0.3f} eV")
    
def p5 () :
    print("\nproblem # 5")
    lmin = 400.0e-9
    lmax = 750.0e-9
    Emax = const.h * const.c / lmin
    Emin = const.h * const.c / lmax
    print(f"5a) Emin = {Emin/const.eV:0.3f} eV")
    print(f"5b) Emax = {Emax/const.eV:0.3f} eV")
    
def p6() :
    print("\nproblem # 6")
    f = 1.8e13
    BE = 10.0 # eV
    gf = 3.2e20
    E = const.h * f / const.eV
    print(f"6a) E = {E:0.3f} eV")
    nphoton = BE / E
    print(f"6b) nphoton = {nphoton:0.3f} -->  {round(nphoton)}")
    Eg = const.h * gf / const.eV
    print(f"6c) E = {Eg:0.3E} eV")
    nmol = Eg/BE
    print(f"6d) n = {nmol:0.3E} -->  {round(nmol)}")
    

def p7() :
    print("\nproblem # 7")
    V = 25.0e3 # V already in eV
    print(f"7a) E = {V:0.3E} eV")
    f = V / (const.h / const.eV)
    print(f"7b) f = {f:0.3E} Hz")
    
def p8() :
    print("\nproblem # 8")
    EV = 105.0e3
    E = EV * const.eV
    p = E/const.c
    print(f"8a) p = {p:0.3E}  kg m / s")
    vn = p / const.mass_n
    print(f"8b) vn = {vn:0.3f}  m/s")
    KE = (1/2) * const.mass_n * vn**2
    print(f"8c) KE= {(KE/const.eV)/1000:0.5f}  keV")

def p9() :
    print("\nproblem # 9")
    vn = 1.05
    p = const.mass_n * vn
    lam = const.h / p
    print(f"9a) lam = {lam*1.0e9:0.2f} nm")
    KE = (p * vn / 2) / const.eV
    print(f"9b) KE= {KE:0.3E} eV")
    
def p10() :
    print("\nproblem # 10")
    V = 315.0
    E = V * const.eV
    lam = const.h / numpy.sqrt(2 * const.mass_e * E)
    print(f"10) lam=  {lam:0.3E} m")
    
def p11() :
    print("\nproblem # 11")
    ve = 1.8e3
    appx = 0.1e-9
    ux = const.h / (4 * numpy.pi * const.mass_e * ve)
    print(f"11a) ux=  {ux*1.0e9:0.3f} nm")
    rat = ux/appx
    print(f"11b) mult=  {rat:0.2f}")
    
def p12() :
    print("\nproblem # 12")
    dt = 2.2e-6
    dm = const.h / (4 * numpy.pi * const.c**2 * dt)
    print(f"12) dm=  {dm:0.3E} kg uncertainty in mass")
    
def p13() :
    print("\nproblem # 13")
    EV = 0.95e12
    E = EV * const.eV
    gam = E / (const.mass_p * const.c**2)
    print(f"13a) gam= {gam:0.3f}")
    p = E/const.c
    print(f"13b) p= {p:0.3E}  kg m / s")
    lam = const.h / p
    print(f"13c) lam= {lam:0.3E} m")


####~~~~


if __name__ == '__main__' :
    main()


########~~~~~~~~END>  hw11_photons.py
