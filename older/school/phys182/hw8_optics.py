"""
    hw8, v3, ch1, c2, optics
"""

import math
import cmath
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
    near_sight = 0.24 # near-sighted person can't see beyond this
    # f = R/2 ...
    d_max = near_sight / 2
    print(f"a) d=  {d_max*100} cm")

def p2() :
    print("\nproblem # 2")
    y = 19
    d_L = 25
    d_R = 52
    tht_L = (1/2) * numpy.math.acos(y/d_L)
    tht_R = (1/2) * numpy.math.acos(y/d_R)
    print(f"a) tht_L=  {numpy.rad2deg(tht_L):0.2f} deg") 
    print(f"b) tht_R=  {numpy.rad2deg(tht_R):0.2f} deg") 

def p3() :
    print("\nproblem # 3")
    d_obj = 19.5
    f = 12.5
    d_img = (f * d_obj) / (d_obj - f)
    print("a) d_img = (f * d_obj) / (d_obj - f)")
    print(f"b) d_img=  {d_img:0.2f}  cm")

def p4() :
    print("\nproblem # 4")
    R = 0.46
    d_img = 2.9
    d_obj = 1 / ((2/R) - (1/d_img))
    mag = -1 * d_img / d_obj
    print(f"a) m=  {mag:0.3f}")

def p5 () :
    print("\nproblem # 5")
    h_obj = 1.35
    d_obj = 3.2
    h_img = 0.173
    m = h_img / h_obj
    d_img = -1 * m * d_obj
    R = 2/((1/d_img) + (1/d_obj))
    print(f"a) m=  {m:0.3f}")
    print(f"b) d_img=  {d_img:0.3f} cm")
    print(f"c) R=  {R:0.3f} cm")


def p6() :
    print("\nproblem # 6")
    print("a) d_img = 2F")
    print("b) the object and image are on the samde side of the mirror and equally(common) distant from the mirror")
    print("c) |h_img| = h_obj")
    print("d) the image is inverted and the same size as the object")
    print("e) the image is a real image because the reflected principle rays physically converage at a common point")

def p7() :
    print("\nproblem # 7")
    f = 200.0e-3
    d_obj = 12.5e3
    h_obj = 850
    d_img = 1 / ((1/f) - (1/d_obj))
    h_img = -1 * (d_img/d_obj) * h_obj
    print(f"a) d_img=  {d_img:0.3f} m")
    print(f"b) h_img= {h_img*100:0.3f} cm")

def p8() :
    P = 0.0045 # W
    I = 110 # W/cm^2
    f = 0.16 # m
    r = 0.0019 # m
    print("\nproblem # 8")
    print("a) rp= [P / (pi I)]^(1/2)  ...sqrt did not work")
    print("b) tan(alpha)= r / f")
    print("c) D= rp / tan(alpha)")
    D = (f/r) * numpy.sqrt(P/(numpy.pi * I))
    print(f"d) D= {D:0.3f} cm")

def p9() :
    print("\nproblem # 9")
    print("a) pick the one with small image, other side of lense, inverted, and past focal point (or see solutions)")
    print("b) the image is real, inverted, and smaller than the object")

def p10() :
    print("\nproblem # 10")
    print("a) see the solution...")
    print("b) the image is virutal, upright, and smaller than the object")

def p11() :
    print("\nproblem # 11")
    d = 25.0
    f_1 = 8.5
    f_2 = 5.4
    h_obj = 4.5
    d_obj = 26.0
    d_img_f1 = 1 / ((1/f_1) - (1/d_obj))
    m_f1 = -1 * (d_img_f1 / d_obj)
    print(f"a) f1, d_img= {d_img_f1:0.3f} cm")
    print(f"b) f1, m= {m_f1:0.3f}")
    print("c) m > 0, upgright :: m < 0, inverted     beyond focal length, it is real     {real and inverted}")
    temp_a = 1 / f_2
    temp_b = 1 / ((1/f_1) - (1/d_obj))
    temp_c = 1 / (d - temp_b)
    d_img_f2 = 1 / (temp_a - temp_c) 
    D = d + d_obj + d_img_f2
    print(f"d) D= {D:0.3f} cm")

def p12() :
    print("\nproblem # 12")
    f1 = 4.7
    f2 = 9.9
    L = 33.9
    d_img = 20.1
    do2 = 1 / ((1/f2) - (1/d_img))
    do1 = 1 / ((1/f1) - (1/(L - do2)))
    print(f"a) do2= {do2:0.3f} cm")
    print(f"b) do1= {do1:0.3f} cm")

def p13() :
    print("\nproblem # 13")
    d_img = 2.0e-2
    d_obj = 3.5
    P = (1/d_img) + (1/d_obj)
    print(f"a) P = {P:0.3f} D")

def p14() :
    print("\nproblem # 14")
    d_obj = 0.305e-2
    f = 0.3e-2
    eye_f = 2.23e-2
    eye_d_obj = 19.51e-2
    d_img = 1 / ((1/f) - (1/d_obj))
    print(f"a) d_img= {d_img*100:0.3f} cm")
    m = -1 * d_img / d_obj
    print(f"b) m= {m:0.3f}")
    eye_d_img = 1 / ((1/eye_f) - (1/(eye_d_obj-d_img)))
    print(f"c) eyepiece d_img= {eye_d_img*100:0.3f} cm")
    eye_m = -1 * eye_d_img / (eye_d_obj-d_img)
    print(f"d) eye_m= {eye_m:0.3f}")
    total_m = eye_m * m
    print(f"e) total m= {total_m:0.3f}")

def p15() :
    print("\nproblem # 15")
    d1_obj = 29.5
    f1 = 8.2
    L = 3.0
    f2 = 11.0
    d1_img = 1 / ((1/f1) - (1/d1_obj))
    print(f"a) d1_img= {d1_img:0.3f} cm")
    m1 = -1 * d1_img / d1_obj
    print(f"b) m1= {m1:0.3f}")
    print(f"c) the image is real and inverted")
    d2_obj = L - d1_img
    print(f"d) d2_obj= {d2_obj:0.3f} cm")
    d2_img = 1/((1/f2) - (1/d2_obj))
    print("e) the object is a virtual object because the incoming rays converge.")
    print(f"f) d2_img= {d2_img:0.3f} cm")
    m2 = -1 * d2_img / d2_obj
    print(f"g) m2= {m2:0.3f}")
    m_net = m1*m2
    print(f"h) total m = {m_net:0.3f}")
    print("i) the final image is real, and it is inverted as compared to the original object.")




####~~~~


if __name__ == '__main__' :
    main()


########~~~~~~~~END>  hw8_optics.py
