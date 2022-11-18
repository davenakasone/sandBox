"""
    ee436 midterm
"""

import math
import cmath
import mpmath
import numpy
import scipy
import sympy
import os
import plotly.graph_objects as go

from juice.pcomplex import pcomplex

c   = 3.0e8                                 # speed of light in a vacuum [m/s]
mu0 = 4 * numpy.pi / numpy.power(10.0, 7.0) # permeability of free space [H/m]
ep0 = 8.854e-12                             # permittivity of free space [F/m]


def main() :
    os.system("clear")
    p1()
    p2()
    print("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n")

def p1() :
    def getZin(l, G, Z0) :
        exponent = complex(0.0, -2 * 2 * l * numpy.pi)
        num = (1 + Gamma * numpy.exp(exponent))
        den = (1 - Gamma * numpy.exp(exponent))
        return (Z0 * (num/den))
    print("\nproblem # 1")
    l = 0.3  # times lamdbda
    Z0 = complex(75.0, 0.0)
    ZL = complex(40.0, 20.0)
    zL = ZL / Z0
    Gamma = (zL - 1) / (zL + 1)
    swr = (1 + numpy.abs(Gamma)) / (1 - numpy.abs(Gamma))
    Zin =  getZin(l, Gamma, Z0)
    zin = Zin/Z0
    print("given:")
    print(f"\tl = {l:0.1f} * lambda")
    pcomplex("\tZ0", Z0)
    pcomplex("\tZL", ZL)
    pcomplex("\tzL", zL)
    print("a) plot zL on the smith chart")
    print("b) measure distance from origin to zL to find |Gamma|, use angle for polar -->")
    pcomplex("\tGamma", Gamma)
    print("c) draw the SWR circle of radius |Gamma|")
    print(f"d) distance on horizontal axis is matched to scale for SWR -->")
    print(f"\tSWR = {swr:0.2f}")
    print("e) draw a radial line from zL, find WTG(wave-lengths toward generator)")
    print(f"f) move down the WTG scale by given l = {l:0.1f} * lambda")
    print("g) zin is inteserction of ray from origin and SWR circle * Z0 -->")
    pcomplex("\tzin", zin)
    pcomplex("\tZin", Zin)
    fig = go.Figure()
    fig.add_trace(go.Scattersmith(
        imag=[0, numpy.imag(zL)],
        real=[1, numpy.real(zL)],
        marker_symbol='x',
        marker_size=10,
        marker_color="green",
        subplot="smith1"
    ))
    fig.add_trace(go.Scattersmith(
        imag=[0, numpy.imag(zin)],
        real=[1, numpy.real(zin)],
        marker_symbol='diamond',
        marker_size=10,
        marker_color="blue",
        subplot="smith1"
    ))
    fig.update_smiths(bgcolor="lightgrey")
    fig.show()

def p2() :
    def fcut(a, b, m, n) :
        t1 = c / (2 * numpy.pi)
        t2 = (m * numpy.pi / a)**2
        t3 = (n * numpy.pi / b)**2
        f = t1 * numpy.sqrt(t2 + t3)
        return f
    def pmode(m, n) :
        if (m == 0) and (n == 0) :
            print("none")
        elif (m == 0) or (n == 0) :
            print("TE only")
        else :
            print("TE and TM")
    def banner(msg, a, b) :
        print(f"\n\n\t{msg}   a=={a*100:0.1f} cm  ;  b=={b*100:0.1f} cm")
        print("\n\t m |  n  |  f_cut (GHz)  |  modes")
        print("\t---------------------------------------")
        
    print("\nproblem # 2a")
    it_m = 5
    it_n = 5
    results = []
    a = 3/100
    b = a / 3
    
    banner("UNSORTED", a, b)
    for m in range(0, it_m) :
        for n in range(0, it_n) :
            temp = fcut(a, b, m, n)
            results.append([m, n, temp])
            print(f"\t{m:2d} |  {n:2d} |  {temp/1.0e9:7.3f}      |  ", end='')
            pmode(m, n)
            
    resultz = numpy.array(results)
    #print(numpy.shape(resultz))
    sortz = resultz[resultz[:,2].argsort()]
    banner("SORTED", a, b)
    for row in sortz :
        print(f"\t{int(row[0]):2d} |  {int(row[1]):2d} |  {row[2]/1.0e9:7.3f}      |  ", end='')
        pmode(row[0], row[1])
    
    low2 = sortz[2,:]
    low3 = sortz[4,:]
    
    print("\n\nQ2b\n")
    print(f"\na=={a*100:0.1f} cm  ;  b=={b*100:0.1f} cm\n")
    f_op = 5 * c / (4 * a)
    print(f"TE_{int(low2[0])}{int(low2[1])}, f_cut=  {low2[2]/1.0e9:7.3f} GHz")
    print(f"f_op=  {f_op/1.0e9:0.3f} GHz")
    print(f"TE_{int(low3[0])}{int(low3[1])}, f_cut=  {low3[2]/1.0e9:7.3f} GHz")
    
    print("\n\nQ2c\n")
    print(f"f_op=  {f_op/1.0e9:0.3f} GHz")
    banner("fcut < fop", a, b)
    for row in sortz :
        mm = int(row[0])
        nn = int(row[1])
        if row[2] < f_op :
            print(f"\t{mm:2d} |  {nn:2d} |  {row[2]/1.0e9:7.3f}      |  ", end='')
            pmode(mm, nn)
    
    print("\n\nQ2d\n")
    bw = c/(2*a)
    print(f"\na=={a*100:0.1f} cm  ;  b=={b*100:0.1f} cm\n")
    print(f"fcut[{int(low2[0])},{int(low2[1])}] = {low2[2]/1.0e9:0.3f} GHz, second lowest")
    print(f"fcut[{int(low3[0])},{int(low3[1])}] = {low3[2]/1.0e9:0.3f} GHz, third lowest")
    print(f"fcut[{int(low3[0])},{int(low3[1])}] - fcut[{int(low2[0])},{int(low2[1])}], ", end='')
    print(f"expected bandwidth    = {(low3[2]-low2[2])/1.0e9:0.3f} GHz")
    print(f"equation, calculated bandwidth               = {bw/1.0e9:0.3f} GHz")

####~~~~


if __name__ == '__main__' :
    main()


########~~~~~~~~END>  midterm.py
