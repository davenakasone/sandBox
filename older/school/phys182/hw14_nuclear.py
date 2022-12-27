"""
    hw14, v3, ch10, nuclear
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
    Na      = 6.02e23                                    # Avogordo #                                [1/mol]
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
    Ei = 30.0
    Edep = 0.55e6
    n = Edep / Ei
    print(f"n= {n:0.2E}")
    
def p2() :
    print("\nproblem # 2")
    rho = 2.3e17
    m = 2.2
    l = (m/rho)**(1/3)
    print(f"l= {l*1.0e6:0.2f} um")
    
def p3() :
    print("\nproblem # 3")
    r = (1.2e-15)*(58)**(1/3)
    print(f"a) r=  {r*1.0e15:0.2f} fm")
    rat = (58/258)**(1/3)
    print(f"b) rat = {rat:0.3f}")
    
def p4() :
    print("\nproblem # 4")
    m_uram = 235.043923 # u
    m_th = 231.036298 # daughter
    m_he = 4.002603 # alpha
    dm = m_uram - m_th - m_he
    eV = dm * 931.5
    print(f"a) MeV= {eV:0.3f}")
    Ea = (m_uram/(m_uram + m_he)) * eV
    print(f"b) Ea =  {Ea:0.3f} MeV")
    
def p5 () :
    print("\nproblem # 5")
    L = 91 * 0.9144       # yd --> m
    L0 = 100              # meters
    rat = L / L0
    vc = numpy.sqrt(1 - rat**2)
    print(f"vc= {vc:0.4f}")
    
def p6() :
    print("\nproblem # 6")
    am_d = 2.014102 # u
    am_t = 3.016049 # u
    mm = 2.75 # kg   !!!
    m_react = am_d + am_t # u
    mols = (mm * 1000) / 5.03
    reactions = mols * const.Na
    E = eV_2_J(reactions * (17.59e6))
    print(f"a) E =  {E:0.3E} J")
    P = E/(3.16e7)
    print(f"b) P= {P/1.0e6:0.2f} MW")
    
    
def p7() :
    print("\nproblem # 7")
    u1 = 0.735
    u2 = 0.955
    vc = (u1 - u2) / (1 - (u1 * u2))
    print(f"vc = {vc:0.4f}")
    
def p8() :
    print("\nproblem # 8")
    hl = 1.405e10 # years
    m = (270e-3) # g
    N = (const.Na / 232) * m
    A = (0.693 / hl) * N
    Bq = A / (365*24*3600)
    print(f"Bq= {Bq:0.1f}")

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
    Pr = 150.0e6 # W
    Edecay = eV_2_J(1.0e6) # J
    A = Pr / Edecay
    R = A / 3.7e10
    print(f"12) Ci= {R:0.3E}")
    
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
    m = 35.5 # g
    N = m * (const.Na / 238.03)
    hl = 4.5e9 * 3.16e7
    R = (0.693 * N) / hl
    print(f"a) Bq=  {R:0.3E}")
    RR = R * 0.9927
    NN = N * 0.0072
    hhl = 7.0e8 * 3.16e7
    A = 0.693 * NN / hhl
    Bq = A + RR
    print(f"b) Bq = {Bq:0.3E}")
    
def p15() :
    print("\nproblem # 15")
    psun = 4.0e26 # W
    sup = 0.95
    pp = psun * sup
    mev = J_2_eV(pp) / 1.0e6
    pro = mev * 4 / 26.7
    print(f"a) protons=  {pro:0.3E}")
    neut = pro/4
    A = numpy.pi * (6.378e6)**2
    print(f"b) rate=  {neut/A:0.3E}")
    


####~~~~


if __name__ == '__main__' :
    main()


########~~~~~~~~END>  hw14_nuclear.py
