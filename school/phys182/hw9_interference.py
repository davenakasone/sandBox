"""
    hw9, v3, ch3, interfernece
"""

import math
import cmath
from re import M
import numpy
#import scipy
#import sympy
import os

c   = 3.0e8                                 # speed of light in a vacuum [m/s]
mu0 = 4 * numpy.pi / numpy.power(10.0, 7.0) # permeability of free space [H/m]
ep0 = 8.854e-12                             # permittivity of free space [F/m]
kr  = 5.67e-8                               # Boltzmann radiaiton constant [J / s m^2 T^4]
h_planck = 6.626e-34                        # Planck constant, photon energy [kg m^2 / s]

def main() :
    os.system("clear")
    # p1()
    # p2()
    # p3()
    # p4()
    # p5()
    # p6()
    # p7()
    # p8()
    # p9()
    # p10()
    # p11()
    # p12() 
    # p13()
    # p14()
    p15()
    print("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n")

def p1() :
    """
        when light enters a different index of refraction, speed and wave length change
        frequency is constant
        change in wavelength is proprotional to change in speed
        n_air = c / v_air
        n_glass = c / v_glass
        n_air / n_glass = v_glass / v_air
    """
    print("\nproblem # 1")
    lam_air = 525.0e-9
    n_air = 1
    n_glass = 1.75
    print("a) lam_glass = lam_air * (n_air / n_glass)")
    print("b) v_glass = v_air * (n_air / n_glass)")
    v_glass = c * (n_air / n_glass)
    print(f"c) v_glass = {v_glass:0.3E} m/s")

def p2() :
    print("\nproblem # 2")
    d = 103.0e-6
    m = 3.0
    tht = numpy.deg2rad(0.61)
    lam = numpy.sin(tht) * d / m
    print(f"a) lam= {lam*1.0e9:0.3f} nm")
    
def p3() :
    print("\nproblem # 3")
    d = 0.022 / 1000.0
    lam = 3750 / 1.0e10
    L = 4.4
    print("a) sin(tht1) = m lam / d  ....m=1 .... lam/d     the first bright fringe")
    print("b) sin(tht2) = m lam / d  ....m=2 .... 2 lam/d     the second bright fringe")
    print("c) y = L{ tan(tht2) - tan(tht1) }")
    tht1 = numpy.arcsin(lam / d)
    tht2 = numpy.arcsin(2 * lam / d)
    y = L * (numpy.tan(tht2) - numpy.tan(tht1))
    print(f"d) y= {y:0.5f} m")

def p4() :
    print("\nproblem # 4")
    th1max = numpy.deg2rad(6.5) # first order, m=1
    ld1 = numpy.sin(th1max)
    th2max = numpy.arcsin(2 * ld1)
    print(f"a) th2max= {numpy.rad2deg(th2max):0.3f} deg")
    th1min = numpy.arcsin((1/2)*ld1)
    print(f"b) th1min= {numpy.rad2deg(th1min):0.3f} deg")
    
def p5 () :
    print("\nproblem # 5")
    x = 2.9
    lam = 635.0 / 1.0e9
    d = 0.0805 / 1.0e3
    print("a) dy = x lam / d")
    dy = x * lam / d
    print(f"b) dy = {dy*100:0.3f} cm")
    
def p6() :
    print("\nproblem # 6")
    lam = 470.0 / 1.0e9
    d = 15.0 / 1.0e6
    L = 2.4
    y = 4.3 / 1.0e3
    I = 85.0
    print("a) phi = 2 pi d y / (lam L)")
    phi = 2 * numpy.pi * d * y / (lam * L)
    print(f"b) phi = {phi:0.4f} rad")
    II = I / (4 * (numpy.cos(phi/2))**2)
    print(f"c) I0= {II:0.3f} W/m^2")
    
def p7() :
    print("\nproblem # 7")
    print("a) plexi-air-plexi, n[1.51:1:1.51] first phase change is 0, second pi, greatest lam in air")
    print("b) diamond-zircon-fluorite, n[2.419:1.923:1.434]: both phase chances are 0, shortest lam in diamond")

def p8() :
    print("\nproblem # 8")
    n_oil = 1.47
    n_water = 1.3
    n_air = 1.0
    lam_air = 375.0e-9
    print("a) lam_oil = lam_air / n_oil      ...lam/n_o")
    print("b) tmin = lam_oil / 2")
    print("c) tmin = lam_air / (2 n_oil)    ...  lam/(2 n_o)")
    tmin = lam_air / (2 * n_oil)
    print(f"d) tmin= {tmin*1.0e9:0.3f} nm")
    
def p9() :
    print("\nproblem # 9")

def p10() :
    print("\nproblem # 10")
    bubble = 115.0e-9
    n_soap = 1.33
    lam = 4 * n_soap * bubble
    print(f"lam = {lam*1.0e9:0.1f} nm")
    
def p11() :
    print("\nproblem # 11")
    slide = 6.5 / 100
    lam = 595.0e-9
    bands = 0.085 / 100
    d = lam * slide / (2 * bands)
    print(f"d= {d:0.3E} m")
    
def p12() :
    print("\nproblem # 12")
    lam = 543.0e-9
    n_oil = 1.22
    n_plasitc = 1.47
    t = (1/2) * (lam/n_oil)
    print(f"a) t= {t*1.0e9:0.3f} nm")

def p13() :
    print("\nproblem # 13")
    lam = 589.0e-9
    bf = 101
    D = lam * (2 * (bf-1) + 1) / 4
    print(f"a) D= {D*1.0e6:0.3f} um")
    dD = (1/2) * lam
    print(f"b) dD= {dD*1.0e6:0.4f} um")
    err = dD / D
    print(f"c) perr= {100*err:0.1f} %")
        
def p14() :
    print("\nproblem # 14")
    kline = 606.0e-9
    fringes = 1400
    d = (1/2) * fringes * kline
    print(f"a) d = {d*1.0e6:0.2f} um")
    
def p15() :
    print("\nproblem # 15")
    lam = 633.0e-9
    d = 4.969 / 100.0
    n = 1.000293
    N0 = (2 * d / lam)
    m = N0 * (n-1)
    print(f"roun to integer, m= {m}")
    
####~~~~


if __name__ == '__main__' :
    main()


########~~~~~~~~END>  hw9_interference.py
