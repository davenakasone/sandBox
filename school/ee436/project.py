"""
    ee436, project
    making 50 ohm microstrip line
        - thin conductor, W @ y>d
        - ground plate @ y=0, thickness = d, ep_r, d << lambda
        - quasi TEM, quasi static solutions
    
    make effective dielectric constant of the microstrip:   1 < ep_e < ep_r
    examples 3.7 and 3.8 have some good formulas:
        phi = beta * l = k0 * l * sqrt(ep_e)
        k0 = 2 pi f / c = w / c
        l = phi / (k0 * sqrt(ep_e))
"""

import math
import cmath
import mpmath
import numpy
import scipy
import sympy
import os
import matplotlib.pyplot as plt

FLAG = -99.99

class Cconst() :
    c       = 3.0e8                       # speed of light in a vacuum           [m/s]
    ep0     = 8.854e-12                   # permittivity of free space           [F/m]
    mu0     = 4 * numpy.pi * 10.0e-7      # permeability of free space           [H/m]
const = Cconst()


def Npm_2_dBm(Npm) :
    """Nepers per meter --> decibels per meter"""
    dBm = Npm * (20 / numpy.log(10))
    return dBm

def dBm_2_Npm(dBm) :
    """decibels per meter --> Nepers per meter"""
    Npm = dBm * (numpy.log(10) / 20)
    return Npm
    
def calc_vp(ep_e) :
    """eqn_3.193, phase velocity v_p"""
    vp = const.c / numpy.sqrt(ep_e)
    return vp

def calc_beta(k0, ep_e) :
    """eqn_3.194, propagation constant beta"""
    beta = k0 * numpy.sqrt(ep_e)
    return beta

def calc_epe(ep_r, d, W) :
    """eqn_3.195, effective dielectric constant"""
    tempA = (ep_r + 1) / 2
    tempB = (ep_r - 1) / 2
    tempC = numpy.sqrt(1 + ((12 * d) / W))
    epe = tempA + tempB * (1 / tempC)
    return epe

def Zchar_wd(ep_e, d, W) :
    """eqn_3.196, characteristic impedance"""
    Z0 = 0
    rat = W/d
    if rat < 1.0 :
        print(f"\nW/d = {rat:0.3f}  ,  using Z0 with W/d < 1")
        Z0 = Zchar_wd_lt1(ep_e, d, W)
    else :
        print(f"\nW/d = {rat:0.3f}  ,  using Z0 with W/d > 1")
        Z0 = Zchar_wd_gt1(ep_e, d, W)
    return Z0

def Zchar_wd_lt1(ep_e, d, W) :
    """eqn_3.196, characteristic impedance, given W/d <= 1"""
    tempA = 60 / numpy.sqrt(ep_e)
    tempB = numpy.log(((8 * d) / W) + (W / (4 *d)))
    Z0 = tempA * tempB
    return Z0

def Zchar_wd_gt1(ep_e, d, W) :
    """eqn_3.196, characteristic impedance, given W/d >= 1"""
    tempA = 120 * numpy.pi
    tempB = (W / d) + 1.393
    tempC = 0.667 * numpy.log((W / d) * 1.444)
    Z0 = tempA / (numpy.sqrt(ep_e) * (tempB + tempC))
    return Z0

def calc_Wd(Z0, ep_r) :
    """eqn_3.197, W/d ratio, given: Z0, ep_r"""
    A, Wda = calc_Wd_lt2(Z0, ep_r)
    print(f"\ntrying W/d < 2,  A= {A:0.3f}  ,  W/d= {Wda:0.5f}")
    B, Wdb = calc_Wd_lg2(Z0, ep_r)
    print(f"trying W/d > 2,  B= {B:0.3f}  ,  W/d= {Wdb:0.5f}")
    if (Wda < 2.0) and (Wdb > 2.0) :
        print("both conditions are satisfied, something is probably wrong")
        return FLAG
    elif (Wda < 2.0) :
        print(f"condition W/d < 2 is satisfied, use W/d=  {Wda:0.5f}")
        return Wda
    elif (Wdb > 2.0) :
        print(f"condition W/d > 2 is satisfied, use W/d=  {Wdb:0.5f}")
        return Wdb
    
def calc_Wd_lt2(Z0, ep_r) :
    """eqn_3.197, W/d ratio, given: W/d < 2, Z0, ep_r"""
    def calc_A(Z0, ep_r) :
        temp_a = (Z0 / 60) * numpy.sqrt((ep_r + 1) / 2)
        temp_b = (ep_r - 1) / (ep_r + 1)
        temp_c = 0.23 + (0.11 / ep_r)
        A = temp_a + temp_b * temp_c
        return A
    AA = calc_A(Z0, ep_r)
    temp_a = 8 * numpy.exp(AA)
    temp_b = numpy.exp(2 * AA) - 2
    Wd = temp_a / temp_b
    return AA, Wd

def calc_Wd_lg2(Z0, ep_r) :
    """eqn_3.197, W/d ratio, given: W/d > 2, Z0, ep_r"""
    def calc_B(Z0, ep_r) :
        temp_a = 377 * numpy.pi
        temp_b = 2 * Z0 * numpy.sqrt(ep_r)
        B = temp_a / temp_b
        return B
    BB = calc_B(Z0, ep_r)
    temp_a = 2 / numpy.pi
    temp_b = BB - 1 - numpy.log(2 * BB - 1)
    temp_c = (ep_r - 1) / (2 * ep_r)
    temp_d = numpy.log(BB - 1) + 0.39 - (0.61 / ep_r)
    Wd = temp_a * (temp_b + temp_c * temp_d)
    return BB, Wd
    
def calc_alphad(k0, ep_r, ep_e, delta) :
    """eqn_3.198, attenuation from dielectric loss"""
    tempA = k0 * ep_r * (ep_e - 1) * numpy.tan(delta)
    tempB = 2 * numpy.sqrt(ep_e) * (ep_r - 1)
    alpha_d = tempA / tempB
    return alpha_d

def calc_alphac(Rs, Z0, W) :
    """eqn_3.199, attenuation from conductor loss, Rs= sqrt(omega * mu0 / (2 * sigma))"""
    alpha_c = Rs / (Z0 * W)
    return alpha_c

def epef(ep_r, ep_e, Z0, d, f) :
    """eqn_3.200, frequeny dependent effective dielectric constant"""
    dd = d * 100     # d in cm
    ff = f / 1.0e9   # f in GHz
    g = 0.6 + 0.009 * Z0
    fp = Z0 / (8 * numpy.pi * dd)
    Gf = g * (ff / fp)**2
    epef = ep_r - ((ep_r - ep_e) / (1 + Gf))
    return epef

def calc_ft1(d, ep_r) :
    """eqn_3.201, TM1 cutoff, threshold is between 0 and here"""
    tempA = const.c / (2 * numpy.pi * d)
    tempB = numpy.sqrt(2 / (ep_r - 1))
    tempC = numpy.arctan(ep_r)
    ft1 = tempA * tempB * tempC
    return ft1

def calc_ft2(d, ep_r) :
    """eqn_3.202, TE1 cutoff"""
    tempA = const.c / (4 * d)
    tempB = 1 / numpy.sqrt(ep_r - 1)
    ft2 = tempA * tempB
    return ft2

def calc_ft3(d, ep_r, W) :
    """eqn_3.203, big cutoff"""
    tempA = const.c / numpy.sqrt(ep_r)
    tempB = 1 / (2 * W + d)
    ft3 = tempA * tempB
    return ft3

def calc_ft4(d, ep_r) :
    """eqn_3.204, wide cutoff"""
    tempA = const.c / numpy.sqrt(ep_r)
    tempB = 1 / (2 * d)
    ft4 = tempA * tempB
    return ft4


####~~~~


def main() :
    os.system("clear")
    #ex37()
    #ex38()
    mystrip(True)
    print("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n")


####~~~~

  
def ex37() :
    # given + copper conductor
    epr = 9.9
    delta = numpy.arctan(0.001)
    d = 0.5e-3
    Z0 = 50.0
    phid = numpy.deg2rad(270.0) # phase delay
    f = 10.0e9
    
    # 0, infer from given information
    omg = 2 * numpy.pi * f
    k0 = omg / const.c
    Rs = 0.026 # lookup copper @ 10 GHz, surface resistance for the conductor
    
    # 1, find W/d ratio
    rat_Wd = calc_Wd(Z0, epr)   # use algebra, given W/d  ->  W = rat * d
    W = rat_Wd * d
    print(f"\nW = {W:0.3E} m")
    
    # 2, find the effective dielectric constant
    epe = calc_epe(epr, d, W)
    print(f"\nep_e=  {epe:0.5f}")
    
    # 3, find length needed for phase delay
    l = phid / (numpy.sqrt(epe) * k0)
    print(f"\nlength=  {l:0.3E} m")
    
    # 4, find attenuation
    a_d = calc_alphad(k0, epr, epe, delta)
    print(f"\nalpha_d=  {a_d:0.5f} Np/m  -->  {Npm_2_dBm(a_d):0.3E} dB/m")
    a_c = calc_alphac(Rs, Z0, W)
    print(f"\nalpha_c=  {a_c:0.5f} Np/m  -->  {Npm_2_dBm(a_c):0.3E} dB/m")
    loss = (Npm_2_dBm(a_c) + Npm_2_dBm(a_d)) * l
    print(f"\ntotal loss=  {loss:0.3E} dB")


####~~~~

 
def ex38() :
    Z0 = 25
    epr = 10.0
    d = 0.65e-3
    l = 1.093e-2
    
    # 1, find W/d ratio
    rat_Wd = calc_Wd(Z0, epr)   # use algebra, given W/d  ->  W = rat * d
    W = rat_Wd * d
    print(f"\nW = {W:0.3E} m")
    
    # 2, find the effective dielectric constant
    epe = calc_epe(epr, d, W)
    print(f"\nep_e=  {epe:0.5f}")
    
    # 3, compare some phase delays using ex3.7 identities
    k0 = 2 * numpy.pi * 10.0e9 / const.c
    phi0 = k0 * l * numpy.sqrt(epe)
    print(f"\nep_e0, phi=  {numpy.rad2deg(phi0):0.3f} deg    no frequency adjustment")
    phi10 = k0 * l * numpy.sqrt(epef(epr, epe, Z0, d, 10.0e9))
    print(f"\nep_e10, phi=  {numpy.rad2deg(phi10):0.3f} deg  with frequency adjustment")
    
    ptz = 500
    freqz = numpy.linspace(0, 20.0e9, ptz)
    epez = numpy.zeros(ptz)
    for ii in range(0, ptz) :
        epez[ii] = epef(epr, epe, Z0, d, freqz[ii])
    plt.title("eqn_3.200, ep_e with frequency consideration")
    plt.xlabel("frequency")
    plt.ylabel("effective dielectric constant")
    plt.plot(freqz, epez, "r-")
    plt.show()
        
    
####~~~~


def mystrip(plot_epef) :
    # given :
    multlam = 10                      # length multiplier (make microstrip > 1 wavelength)
    epr     = 4.2                     # datasheet makes this claim at 1 GHz, always < 5.4
    Rs      = 0.026                   # known material property
    Z0      = 50.0                    # given target
    d       = 1.6e-3                  # data sheet
    phid    = numpy.deg2rad(360.0)    # irrelevant
    delta   = numpy.arctan(0.001)     # known material property
    ftarget = 20.0e9                  # make high enough to keep wave length reasonable
    print("\ngiven:")
    print(f"\tep_r  =  {epr:0.2f}, relative dielectric constant of the choosen slab")
    print(f"\tRs    =  {Rs:0.3f} ohms, copper surface resistance in GHz range")
    print(f"\tZ0    =  {Z0:0.1f} ohms,  target characteristic impedance to design")
    print(f"\td     =  {d*1.0e3:0.1f} mm,  smallest dielectric thickness that can be made by hand")
    print(f"\tphi   =  {numpy.rad2deg(phid):0.1f} deg, phase delay through the microstrip")
    print(f"\tdelta =  {numpy.rad2deg(delta):0.1f} deg, loss tangent expected")
    print(f"\tf     =  {ftarget/1.0e9:0.3f} GHz, design frequency")
    
    print("\n# 0, infer from given information :")
    omg = 2 * numpy.pi * ftarget
    k0 = omg / const.c
    print(f"\tomega =  {omg:0.3E} rad/sec")
    print(f"\tk0    =  {k0:0.3E}")
    
    print("\n# 1,  find W/d ratio :")
    rat_Wd = calc_Wd(Z0, epr)   # use algebra, given W/d  ->  W = rat * d
    W = rat_Wd * d
    print(f"\nW =  {W:0.3E} m")
    
    print("\n# 2,  find the effective dielectric constant :")
    epe = calc_epe(epr, d, W)
    print(f"\tep_e =  {epe:0.5f}, unadjusted")
    # and plot the ep_e across frequency
    if plot_epef == True :
        ptz = 500
        freqz = numpy.linspace(0, 40.0e9, ptz)
        epez = numpy.zeros(ptz)
        for ii in range(0, ptz) :
            epez[ii] = epef(epr, epe, Z0, d, freqz[ii])
        plt.title("eqn_3.200, ep_e with frequency consideration")
        plt.xlabel("frequency")
        plt.ylabel("effective dielectric constant")
        plt.plot(freqz, epez, "r-")
        plt.show()
    
    print("\n# 3,  find length needed for phase delay :")
    l0 = phid / (k0 * numpy.sqrt(epe))
    lf = phid / (k0 * numpy.sqrt(epef(epr, epe, Z0, d, ftarget)))
    print(f"\tl =  {l0:0.7E}, ep_e unadjusted")
    print(f"\tl =  {lf:0.7E}, ep_e adjusted for target f = {ftarget/1.0e9:0.1f} GHz")
    
    print("\n# 4,  find attenuation :")
    a_d = calc_alphad(k0, epr, epe, delta)
    print(f"\talpha_d    =  {a_d:0.5f} Np/m  -->  {Npm_2_dBm(a_d):0.3E} dB/m")
    a_c = calc_alphac(Rs, Z0, W)
    print(f"\talpha_c    =  {a_c:0.5f} Np/m  -->  {Npm_2_dBm(a_c):0.3E} dB/m")
    loss = (Npm_2_dBm(a_c) + Npm_2_dBm(a_d)) * l0
    print(f"\ttotal loss =  {loss:0.3E} dB")
    
    print("\n# 5,  find the velocities :")
    vp = calc_vp(epe)
    beta = calc_beta(k0, epe)
    print(f"\tvp   = {vp:0.3E} m/s, quasi-static TEM phase velocity")
    print(f"\tbeta = {beta:0.3E} m/s, quasi-static TEM propagation constant")
    
    print("\n#6,  confirm the threshold frequencies (operate below these) :")
    ft1 = calc_ft1(d, epr)
    ft2 = calc_ft2(d, epr)
    ft3 = calc_ft3(d, epr, W)
    ft4 = calc_ft4(d, epr)
    print(f"\tf_operate =  {ftarget/1.0e9:0.3f} GHz, also target/design frequency")
    print(f"\tft1       =  {ft1/1.0e9:0.3f} GHz, TM1 cutoff, within 35% - 66% of fc1")
    print(f"\tft2       =  {ft2/1.0e9:0.3f} GHz, TE1 cutoff")
    print(f"\tft3       =  {ft3/1.0e9:0.3f} GHz, wide cutoff")
    print(f"\tft4       =  {ft4/1.0e9:0.3f} GHz, thick cutoff")
    
    print("\n# 7,  confirm the results :")
    lam = const.c / ftarget
    mlen = lam * multlam
    print(f"\td      =  {d:0.3E} m                       ,  thickness of the dielectric")
    print(f"\tW      =  {W:0.3E} m                       ,  width of the microstrip")
    print(f"\tlamda  =  {lam:0.3E} m                     ,  wavelength")
    print(f"\tlength =  {mlen:0.3E} m                    ,  how long to size the microstrip -->  {multlam} wavelengths")
    print(f"\tZ0     =  {Zchar_wd(epe, d, W):0.3f} ohms  ,  target = {Z0:0.3f} ohms")
    
    
####~~~~


if __name__ == '__main__' :
    main()


########~~~~~~~~END>  project.py
