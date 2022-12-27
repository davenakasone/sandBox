"""
    hw13, v3, ch7, 8, 9, quantum
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
    h       = 6.626e-34                                  # Planck constant, photon energy            [kg m^2 / s]  
    hbar    = h / (2 * numpy.pi)                         # ...hbar = h / (2 pi)
    kb      = 1.38e-23                                   # regular Boltzmann constant                [J/K]
    kr      = 5.67e-8                                    # Boltzmann radiaiton constant              [J / s m^2 T^4]
    lamC    = 2.43e-12                                   # h/(m0 c) == Compton wavelength            [m]
    lmaxT   = 2.898e-3                                   # relates peak wave length and temperature  [m K]
    mass_e  = 9.109e-31                                  # mass of electron                          [kg]
    mass_n  = 1.675e-27                                  # mass of neutron                           [kg]  
    mass_p  = 1.673e-27                                  # mass of a proton                          [kg]  ?
    mu0     = 4 * numpy.pi / numpy.power(10.0, 7.0)      # permeability of free space                [H/m]
    mub     = 9.3e-24                                    # Bohr magneton                             [J/T] 
    rbhor   = 5.292e-11                                  # Bhor radius, a0                           [m]
    RH      = 1.097e7                                    # Rydberb constant == E0/(hc)               [1/m]
const = Cconst()

def lorentz(v: float) -> float :
    return (1 / numpy.sqrt(1 - (v**2 / const.c**2)))

def eV_2_J(eV) :
    return eV * const.eV

def J_2_eV(J) :
    return J / const.eV


####~~~~

                     
def main() :
    os.system("clear")
    #p1()
    #p2()
    #p3()
    #p4()
    #p5()
    #p6()
    p7()
    print("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n")

def p1() :
    print("\nproblem # 1")
    d = 0.75
    r = d / 2
    r_e = 1.0e-10
    r_n = 1.0e-15
    orbit = (r * r_e) / r_n
    print(f"{orbit:0.1f} m")
    
def p2() :
    print("\nproblem # 2")
    lama = 1 / (const.RH * ((1/1**2) - (1/3**2)))
    print(f"a) lam = {lama*1.0e9:0.3f} nm")
    lamb = 1 / (const.RH * ((1/2**2) - (1/3**2)))
    print(f"b) lam = {lamb*1.0e9:0.3f} nm")
    
def p3() :
    def get_eV(z) :
        return (-1 * z**2 * (13.6) * ((1/4**2) - (1/1**2)))
    print("\nproblem # 3")
    print(f"a) E_he =  {get_eV(2):0.2f} eV")
    print(f"b) E_li =  {get_eV(3):0.2f} eV")
    print(f"c) E_be =  {get_eV(4):0.2f} eV")
    
def p4() :
    print("\nproblem # 4")
    n = 4
    print(f"if n={n}, m_l : +/-   3,2,1,0")
    
def p5 () :
    print("\nproblem # 5")
    n = 3
    print(f"N = {2*n**2}")
    
def p6() :
    print("\nproblem # 6")
    print("square well, x[0:L],  Psi(x) = A cos(kx) does not go to 0 @ boundaries...")
    
def p7() :
    print("\nproblem # 7")
    E = 2.4 # eV
    num = (numpy.pi * const.hbar)**2
    den = 2 * (const.mass_e) * eV_2_J(E)
    L = numpy.sqrt(num/den)
    print(f"L =  {L*1.0e9:0.3f} nm")


####~~~~


if __name__ == '__main__' :
    main()


########~~~~~~~~END>  hw13_quantum.py
