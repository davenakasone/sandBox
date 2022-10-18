"""
    hw7, v2, ch16, light
"""

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
    # p15()

def p1() :
    B0 = 2.5e-6
    w = 3.5e7
    print("a) E0 = c B0")
    E0 = c * B0
    print(f"b) E0 = {E0} V/m")
    f = w / (2 * numpy.pi)
    print("c) f = w(2 pi)")
    print("d) lam= 2 pi c / w")
    l = 2 * c * numpy.pi / w
    print(f"e) lam = {l} m")

def p2() :
    B = 5.5e-4
    E = c * B
    print(f"a) E= {E/1000} kV/m")

def p3() :
    f1 = 1.4e9
    f2 = 169.0
    v = (f2/f1) * c / 2
    print(f"v = {v}")


def p4() :
    t = 3.1e-6
    E0 = 0.69 # N/C
    f = 870.0e3
    w = 2 * numpy.pi * f
    l = c / f
    print(f"a) lam= {l}")
    Et = E0 * numpy.sin(w * t)
    print(f"b) E(t)=  {Et}")

def p5 () :
    P = 65.0e3
    d = 21e3 
    I = P / (4 * numpy.pi * d**2)
    print(f"a) I = {I}")
    E0 = numpy.sqrt(2 * I / (c * ep0))
    print(f"b) E0=  {E0}")

def p6() :
    b = 1.5e13
    d = 4.5
    E0 = 7.5e-6
    I = c * ep0 * E0**2 / 2
    print(f"a) I = {I}")
    A = numpy.pi * (d/2)**2
    P = I * A
    print(f"b) P =  {P}")
    prad = I * b
    print(f"c) {prad} W")

def p7() :
    m = 0.375 # kg
    dT = 45.0 # C
    dt = 120 # s
    k = 3.76e3 # specific heat, J/(kg C)
    P = m * k * dT / dt
    print(f"a) P= {P}")
    d = 19.5/100
    A = numpy.pi * (d/2)**2
    I = P / A
    print(f"b) I = {I}")
    E0 = numpy.sqrt(2*I/(c*ep0))
    print(f"c) E0 = {E0}")
    B0 = E0/c
    print(f"d) B0=  {B0}")

def p8() :
    print("t = r / c")
    print("E = P t")
    print("E = P r / c")

def p9() :
    print("a) I = P / (4 pi r0^2)")
    print("b) U = P r0 / c")

def p10() :
    beam_f = 590e12
    beam_pss = 3.1e41
    F_absorb = 0.8 * h_planck * beam_f * beam_pss / c
    print(f"a) F = {F_absorb}")
    F_refelect = 2 * 0.8 * h_planck * beam_f * beam_pss / c
    print(f"b) F = {F_refelect}")
    print("c) F=  h fs ns A / (2 pi c d^2)")
    F = h_planck * (2.2e65) * (590e12) * 249.5 / (c * 2 * numpy.pi * (11e11)**2)
    print(f"d) F = {F}")

def p11() :
    print("sqrt(2 m v / (t ep0 pi r^2))")

def p12() :
    print("p= 2 Pv / (4 c pi r^2)")

def p13() :
    f1 = 900.0e6
    f2 = 2560.0e6
    lam1 = c/f1
    lam2 = c/f2
    print(f"a) lam1= {lam1*100} cm")
    print(f"b) lam2= {lam2*100} cm")

def p14() :
    lam = 187e-9
    f = c / lam 
    print(f"a) f = {f}")
    pu = 1/lam
    lamo = 380e-9
    prec = ((1/lam) - (1/lamo)) * lamo * 100
    print(f"b) presion=  {prec}")

def p15() :
    A = 1
    emist = 0.9
    Te = 15 + 273
    Ts = 2.7
    P = A * kr * emist * (Te**4 - Ts**4)
    print(f"a) P = {P} W")
    I = 800 # W/m^2, but only half absorbed
    fr = P/(I/2)
    print(f"b) {fr}")
    B = numpy.sqrt((2*P*mu0/c))
    print(f"c) B= {B*1.0e6} uT")


####~~~~


if __name__ == '__main__' :
    main()


########~~~~~~~~END>  hw7_light.py
