"""
    hw6, v1, ch17, sound
"""

import numpy
import scipy
import sympy
import os


def main() :
    os.system("clear")
    ###p1()
    #p2()
    #p3()
    #p4()
    #p5()
    #p6()
    #p7()
    #p8()
    #p9()
    #p10()
    p11()
    #p12() 
    #p13()
    #p14()
    #p15()

def p1() :
    print("fuck you")

def p2() :
    T = 56.0 + 273.0
    v_s = 331.0 * numpy.sqrt(T/273.0)
    print(f"a)  v_s =  {v_s:0.2f}")

def p3() :
    I_0 = numpy.power(10.0, -12.0)
    db = 15.0
    I = numpy.power(10.0, db/10) * I_0
    print(f"a) I =  {I}")

def p4() :
    dogs = 14.0
    beta = 85.0 # dBm for single dog
    I_0 = numpy.power(10.0, -12.0)
    I = numpy.power(10.0, beta/10) * I_0
    beta2 = 10 * numpy.log10((I+I)/I_0)
    print(f"a) 2 dogs:  {beta2}  dB")
    check = beta + 10*numpy.log10(2) # 2x intensity ...   10log10(base) + 10log10(#dogs)
    print(f"check    :  {check}")
    betan = 10*numpy.log10((dogs*I)/I_0)
    print(f"b) {dogs} dogs :  {betan} dB")
    check = beta + 10*numpy.log10(dogs)
    print(f"check        :  {check}")

def p5 () :
    P_1 = 195.0e-6
    P_2 = 1.28 * P_1
    d1d2 = numpy.sqrt(P_1/P_2)
    print(f"a) d1/d2 :  {d1d2}")
    I = P_2 / (numpy.pi * numpy.power(0.01/2, 2))
    print(f"b) I =  {I}  W/m^2")

def p6() :
    v = 340.0 # m/s
    f_1 = 95.0 # Hz
    f_2 = 79.0 # Hz
    print("a) vs = v (f1 - f2) / (f1 + f2)")
    vs = v * (f_1 - f_2) / (f_1 + f_2)
    print(f"b) vs =  {vs}  m/s")
    print("c) fs = (2 f1 f2) / (f1 + f2)")
    fs = (2 * f_1 * f_2) / (f_1 + f_2)
    print(f"d) fs=  {fs} Hz")

def p7() :
    dif = 0.006
    f = 470
    f_low = (1 - dif) * f
    f_hi = (1 + dif) * f
    print(f"a) f_low=  {f_low}  Hz")
    print(f"b) f_hi=  {f_hi}  Hz")

def p8() :
    print(f"a) fb=  {264-220} Hz")
    print(f"b) fb=  {352-297} Hz")
    print(f"c) fb=  {264-132.6} Hz")

def p9() :
    L = 0.74 # m
    tension = 106.0 # N
    rho = 7800.0 # kg/m^3, density of string
    r = 5.6e-4 # m, radius of string
    A = 0.002 # m, amplitude of wave formerd on string
    V = numpy.pi * numpy.power(r, 2) * L
    m = rho * V
    u = m/L
    print(f"a) u =  {u}  kg/m")
    v = numpy.sqrt(tension/u)
    print(f"b) v=  {v}  m/s")
    print("c) alpha = kx-wt    propogates +x")
    print("d) alpha = kx+wt     propogates -x")
    print("e) 2 A cos(wt) sin(kx)   known combination equation")
    print("f) for 4th harmonic, pick graph with 4x anti-notes")

def p10() :
    L = 2.5 # m
    t = 1.5 # s, this is for traveling down and back...2L
    d = L + L
    v = d/t
    m = 0.39 # kg, total mass of slinky
    print(f"a) v =  {v}  m/s")
    f_3 = (3 * v) / (2 * L)
    print(f"b) f3 =  {f_3}  Hz")
    T = (v**2) * (m/L)
    print(f"c) Teff =  {T} N")

def p11() :
    ffun = 146.8 # Hz, for properly tuned D-string
    L = 0.64 # m, oscillating length
    LL = L - 0.11 # m, string shortens after finger is placed
    m = 1.3e-3 # kg, mass of string
    u = m/L  # kg/m   mass per unit length
    tension = u * (2 * L * ffun)**2
    print(f"a) T =  {tension} N")
    f_3 = 3 * ffun
    lam3 = numpy.sqrt(tension/u) / f_3
    print(f"b) lam3 =  {lam3}  m")
    print(f"c) f3 =  {f_3} Hz")
    ff = numpy.sqrt(tension/(m/LL)) / (2 * LL)
    print(f"d) f'=  {ff}  Hz")

def p12() :
    print("fuck you")

def p13() :
    print("fuck you")

def p14() :
    print("fuck you")

def p15() :
    print("fuck you")


####~~~~


if __name__ == '__main__' :
    main()


########~~~~~~~~END>  hw6_sound.py
