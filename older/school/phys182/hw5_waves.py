"""
    hw5, v1, ch16, waves
"""

import numpy
import scipy
import sympy
import os

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


def p1() :
    print(f"a)  v = c / lambda     m/s")
    c = 3.0e8
    lamb = 538.0e-9
    v = c/lamb
    print(f"b)  v = {v}  m/s")
    cycles = 3 # find time to make 3 full cycles
    t = cycles * (1/v)
    print(f"c) t=  {t} s")

def p2() :
    n = 5 # crests observed
    t = 3.8 * 60 # over this period of time
    print(f"a)  f = n/t     crests/time")
    f = n / t
    print(f"b)  f = {f}  Hz")

def p3() :
    B = 2.28e9 # Pa
    rho = 1039 # kg/m^3
    v = numpy.sqrt(B/rho)
    f = 1e3 # Hz
    d = 1e3 # meters
    lam = v/f
    t = d/v
    print(f"a) t= {t}")
    fullz = d/lam
    print(f"b) full waves:  {fullz}")

def p4() :
    # given:  y(x,t) = A sin(kx-wt + phase)
    # 4.5 sin( 2.9 x - 11.8 t + 0.48)
    A = 4.5
    k = 2.9
    w = 11.8
    ph = 0.48
    f = w / (2 * numpy.pi)
    lam = (2 * numpy.pi) / k
    v = w/k
    print(f"a) A  =  {A}")
    print(f"b) f  =  {f}")
    print(f"c) lam=  {lam}")
    print(f"d) v  =  {v}")
    print(f"e) ph =  {ph}")

def p5 () :
    L = 3.3
    m = 0.75
    t1 = 1.7
    u = m / L
    v = L / t1
    tension = (v**2) * u
    t2 = 0.15
    h2 = 0.15
    w2 = v * t2
    h_speed = (2 * h2) / t2
    print(f"a) F_tension = {tension}")
    print(f"b) width =  {w2}")
    print(f"c) avg h speed=  {h_speed}")

def p6() :
    L = 0.25 # how far rumble strips are spaced .. also lambda here
    d = 1/100 # how deep the rumble strip groves are "amplitude"
    f = 67 # how much your tires oscillate
    t = 1.1
    y = (1/2) * d * numpy.sin(2 * numpy.pi * f * t)
    v = f * L # m/s
    kmph = v * (3600/1000)
    print("a)      (1/2) d sin(2 pi f t)")
    print(f"b) y =  {y*100} cm")
    print(f"c) kmph= {kmph}")
    print("d)  y(x,t)=    (1/2) d sin( [2 pi / L] x - 2 pi f t)")

def p7() :
    L  = 33/100 # string length on violin
    f_4 = 785
    lam_4 = (2 * L) / 4    # figure a appears to have n= this number
    v = f_4 * lam_4
    lam_fun = (2 * L) / 1
    f_fun = v / lam_fun
    f_8 = 8 * f_fun
    print("a) count the times the function touches the horizontal axis, including ends, should be 5")
    print("b) count the max/min, should be 4")
    print(f"c) lam_a = {lam_4} m")
    print(f"d) f_fun =  {f_fun} Hz")
    print("e) it is double...  2 f1")
    print("f) f_n = n * f1")
    print(f"g) f8 = 8 f_fun = {f_8} Hz")

def p8() :
    print("a) superposion when: waves pass through eachother + transverse has reflections")
    print("b) t/f, destructive interfecne is result of superposition for in phase waves:  false...they are inphase")

def p9() :
    v1 = 0.21
    v2 = 0.23
    d = 2.13
    dt = d / (v1 + v2)
    A1 = 3.26/100
    A2 = 1.9/100 
    A = A1 + A2
    A_inv = A1 - A2
    print(f"a) they will meet at dt=  {dt} s")
    print(f"b) combined A = {A*100} cm")
    print(f"c) combined A = {A_inv*100} cm")
    print("d) after passing, waves retain their same velocity...")

def p10() :
    tension = 139
    m = 8/1000
    v = 320
    temp = tension / (v**2)   # u = m / L
    L = m * (1/temp) # it is a wave length
    f = v / L
    print(f"a) L=  {L} m")
    print(f"b) f = {f} Hz")

def p11() :
    L = 0.56
    u = 0.0089
    v = 82.41 # Hz?
    vv = 330
    tension = (v * 2 * L)**2 * u
    tensionn = (vv * 2 * L)**2 * u
    print(f"a) T =  {tension}  N")
    print(f"b) T =  {tensionn}  N")

def p12() :
    M = 1700
    g = 9.8
    tension = M * g
    L = 4.6
    rho = 1.3
    f = (1/(2*L)) * numpy.sqrt(tension/rho)
    m_new = rho*(L * f)**2 / g
    print("a) f= (1 / 2L) sqrt(Mg / rho)")
    print(f"b)  f = {f} Hz")
    print(f"c)  mass =  {m_new} kg")

def p13() :
    sympy.init_printing(use_unicode=False, wrap_line=True)
    x = sympy.Symbol("x")
    t = sympy.Symbol("t")
    c = sympy.Symbol("c")
    vv = sympy.Symbol("vv")
    A = sympy.Symbol("A")

    f = A * sympy.log(x -c*t)
    vv = c**2 / 1
    df_tt = sympy.diff(f, t, 2)
    df_xx = sympy.diff(f, x, 2)
    print(f"df_xx :  {df_xx}")
    print(f"df_tt :  {df_tt}")
    check = df_xx - (df_tt * (1/vv))
    print(f"check:  {sympy.simplify(check)}\n")

    f = A * (x**2 - (c*t)**2)
    vv = c**2 / 1
    df_tt = sympy.diff(f, t, 2)
    df_xx = sympy.diff(f, x, 2)
    print(f"df_xx :  {df_xx}")
    print(f"df_tt :  {df_tt}")
    check = df_xx - (df_tt * (1/vv))
    print(f"check:  {sympy.simplify(check)}\n")

    f = A * (x -  c*t)**3
    vv = c**2 / 1
    df_tt = sympy.diff(f, t, 2)
    df_xx = sympy.diff(f, x, 2)
    print(f"df_xx :  {df_xx}")
    print(f"df_tt :  {df_tt}")
    check = df_xx - (df_tt * (1/vv))
    print(f"check:  {sympy.simplify(check)}")
    
    print("\nif is has (kx-wt)  it is good...")

def p14() :
    P1 = 11.5e3
    A1 = 1.05
    A2 = 0.55
    # using P1/P2 = (A1/A2)^2   -->  P2 = P1 (A2/A1)^2
    P2 = P1 * (A2/A1)**2
    print(f"a) P2 =  {P2/1000} kW")

def p15() :
    absorbed = 0.9 # 90% of the beam is absorbed
    d = 2.05/1000 # diameter of spot
    r = d/2
    area = numpy.pi * r**2
    E = 525
    t = 4.25
    P = E / t
    I = P / (area * absorbed)
    print(f"I=  {I} W/m")


####~~~~


if __name__ == '__main__' :
    main()


########~~~~~~~~END>  hw5_waves.py
