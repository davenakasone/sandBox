"""
    hw10, v3, ch4, diffraction
"""

import math
import cmath
import mpmath
import numpy
import scipy
import sympy
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
    print("\nproblem # 1")
    w = 1.5e-6
    lamv = 405.0e-9
    lamr = 710.0e-9
    thtv = numpy.arcsin(1 * lamv / w)
    print(f"a) thtv = {numpy.rad2deg(thtv):0.3f} deg")
    thtr = numpy.arcsin(1 * lamr / w)
    print(f"b) thtr = {numpy.rad2deg(thtr):0.3f} deg")
    

def p2() :
    print("\nproblem # 2")
    m = 3
    tht_min3 = numpy.deg2rad(23.9)
    w = 3.85e-6
    lam = w * numpy.sin(tht_min3) / m
    print(f"a) lam = {lam*1.0e9:0.3f} nm")

def p3() :
    print("\nproblem # 3")
    w = 51.0
    lam = 21.5
    print("find the angle the biggest valid angle:")
    for m in range(1, 5) :
        div = m*lam/w
        if (div > 1) or (div < -1) :
            print("iterations complete, max is last printout")
            break
        tht = numpy.arcsin(div)
        print(f"m={m}, tht = {numpy.rad2deg(tht):0.3f} deg")
    
def p4() :
    print("\nproblem # 4")
    dhl = 1.05
    lam = 555.0e-9
    a = 0.4 / 100.0
    D = dhl * a / (1.22 * lam)
    print(f"dmin= {D/1.0e3:0.3f} km")
    
def p5 () :
    print("\nproblem # 5")
    res = 11.0 / 100.0
    h = 210.0 * 1.0e3
    lam = 550.0e-9
    tht_max = numpy.tan(res/h)
    D = 1.22 * lam / tht_max
    print(f"D= {D:0.3f} m")
    
def p6() :
    print("\nproblem # 6")
    D = 3.2 / 1.0e3
    dh = 1.45
    lam = 550.0e-9
    dd = 0.8
    tht_min = numpy.arcsin(1.22 * lam / D)
    print(f"a) tht_min= {tht_min:0.3E} rad")
    L = dh / tht_min
    print(f"b) L = {L/1.0e3:0.3f} km")
    d = tht_min * dd
    print(f"c) d= {d*1.0e3:0.3f} mm")
    
def p7() :
    print("\nproblem # 7")
    lam = 538.0e-9
    n = 1100 * 100 # lines per cm --> lines per meter
    d = 1 / n
    m = 1
    tht = numpy.arcsin(m * lam / d)
    print(f"a) tht1= {tht:0.5f} rad")
    m = 4
    tht = numpy.arcsin(m * lam / d)
    print(f"a) tht4= {tht:0.5f} rad")
    
def p8() :
    print("\nproblem # 8")
    lam = 470.0e-9
    tht = numpy.deg2rad(28.0)
    m = 1.0
    n = numpy.sin(tht) / (m * lam * 100.0)
    print(f"n = {n:0.3f} lines/cm")
    
def p9() :
    def get_tht(m, lam, n) :
        return numpy.rad2deg(numpy.arcsin(m * n*100 * lam))
    print("\nproblem # 9")
    lam1 = 403.0e-9
    lam2 = 421.0e-9
    lam3 = 528.0e-9
    lam4 = 686.0e-9
    n = 5000.0 # lines per cm
    m = 1
    print(f"a) tht11= {get_tht(m, lam1, n):0.3f} deg")
    print(f"b) tht21= {get_tht(m, lam2, n):0.3f} deg")
    print(f"c) tht31= {get_tht(m, lam3, n):0.3f} deg")
    print(f"d) tht41= {get_tht(m, lam4, n):0.3f} deg")
    m = 2
    print(f"e) tht12= {get_tht(m, lam1, n):0.3f} deg")
    print(f"f) tht22= {get_tht(m, lam2, n):0.3f} deg")
    print(f"g) tht32= {get_tht(m, lam3, n):0.3f} deg")
    print(f"h) tht42= {get_tht(m, lam4, n):0.3f} deg")
    
def p10() :
    print("\nproblem # 10")
    n = 30500 # lines / cm
    lam = 1 / (n * 100)
    print(f"a) lam = {lam*1.0e9:0.3f} nm")
    laml = 700.0e-9
    m = 2
    N = 1 / (2 * 100 * laml)
    print(f"b) N = {N:0.3f} lines/cm")
    
def p11() :
    print("\nproblem # 11")
    I0 = 650.0
    tp2 = numpy.deg2rad(45.0)
    I1 = I0 / 2
    print(f"a) I1= {I1:0.1f} W/m^2")
    I2 = I1 * (numpy.cos(tp2))**2
    print(f"b) I2= {I2:0.3f} W/m^2")
    
def p12() :
    print("\nproblem # 12")
    I0 = 125.0
    tht = numpy.deg2rad(86.0)
    I1 = I0 * (numpy.cos(tht))**2
    print(f"I = {I1*1.0e3:0.3f} mW/m^3")
    
def p13() :
    print("\nproblem # 13")
    ng = 1.46
    nw = 1.33
    thtb = numpy.arctan(nw/ng)
    print(f"thtb= {numpy.rad2deg(thtb):0.3f} deg")
    
def p14() :
    print("\nproblem # 14")
    lam = 0.105e-9
    d = 0.541e-9
    tht = numpy.arcsin(lam/(2*d))
    print(f"tht= {numpy.rad2deg(tht):0.3f} deg")
    
def p15() :
    print("\nproblem # 15")
    tht11 = numpy.deg2rad(27.1)
    lam2 = 0.141e-9
    tht22 = numpy.deg2rad(39.5)
    d = lam2 / numpy.sin(tht22)
    print(f"a) d= {d*1.0e9:0.3f} nm")
    lam1 = 2 * d * numpy.sin(tht11)
    print(f"b) lam1 = {lam1*1.0e9:0.3f} nm")
    
    
####~~~~


if __name__ == '__main__' :
    main()


########~~~~~~~~END>  hw10_diffraction.py
