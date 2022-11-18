"""
    ee442, project
    make a flyback converter [100:130] VAC --> 5V, 1A for USB 2.0
"""
import os
import sys
import numpy

from juice.para import para
from juice.ltc6992 import Ltc6992

target_Vout = 5.0
target_Iout = 1.0

# flyback transformer, wurth 750811617
fb_Rpri = 1.595                   # DC resistance, primary coil [1:3]
fb_Rsec = 0.0119                  # DC resistance, secondary coil [7:10]
fb_Raux = 0.377                   # DC resistance, auxillary coil [5:6]
fb_Lpri = 793.0e-6                # primary inductance
fb_leak_min = 8.91e-6             # minimum leakage inductance from primary to other coils
fb_leak_max = 13.37e-6            # maximum leakage inductance from primary to other coils
fb_dielectric_pri_sec = 4500.0    # VAC for about 1 second
fb_dielectric_pri_aux = 650.0     # VAC for about 1 second, 500 VAC for 1 minute
fb_n_pri_sec = 20.0/1.0           # turns ratio, primary to secondary
fb_n_pri_aux = 16.0/1.0           # turns ratio, primary to auxillary

# oscillator, LTC6992, main
#osc_main = Ltc6992(100.0e3, 0.6, 0, "main")
#osc_starter = Ltc6992(75.0e3, 0.5, 0, "starter")

# osc_starter = Ltc6992(50.0e3, 0.5, 0, "starter")
# osc_main = Ltc6992(150.0e3, 0.5, 0, "main")

# osc_starter = Ltc6992(25.0e3, 0.5, 0, "starter")
# osc_main = Ltc6992(50.0e3, 0.25, 0, "main")

# osc_starter = Ltc6992(125.0e3, 0.5, 0, "starter")
# osc_main = Ltc6992(125.0e3, 0.75, 0, "main")

# osc_starter = Ltc6992(80.0e3, 0.5, 0, "starter")
# osc_main = Ltc6992(80.0e3, 0.75, 0, "main")

# osc_starter = Ltc6992(80.0e3, 0.5, 0, "starter")
# osc_main = Ltc6992(150.0e3, 0.3, 0, "main")

def main() -> None :
    os.system("clear")
    # osc_main.oprint()
    # osc_starter.oprint()
    # rtop(3, 4.5, 10e3, True)
    
    oscit(159e3, 162e3, 1e3)
    print("\n\n")
    eval_osc(90e3, 110e3, "starter")
    eval_osc(60e3, 18e3, "main")
   
    print("\n\n~ ~ ~ PROGRAM COMPELTE ~ ~ ~\n\n")
    sys.exit()

def rtop(V_div, V_in, R_bot, rprint=True) :
    lam = V_div / V_in
    R_top = R_bot * ((1/lam) - 1)
    if rprint == True :
        print(f"\nfor V_div = {V_div:0.1f}, given V_in = {V_in:0.1f}::  top= {R_top:0.1f}  bot={R_bot:0.1f}")
    return R_bot

def eval_osc(s_top, s_bot, name) :
    nd = 4
    r_set = s_top + s_bot
    f = 50.0e9 / (nd * r_set)
    T = 1 / f
    vmod = s_bot/(s_bot+s_top)
    D = (vmod/0.8)-(1/8)
    print(f"\n{name}")
    print(f"f = {f/1.0e3:0.1f} kHz")
    print(f"T = {T*1.0e6:0.1f} us")
    print(f"D = {D*100:0.1f} %")

def oscit(startf, stopf, fstep) :
    def pban() :
        print("\nD     |   f  kHz  |  T  us     | top  kohm |  bot  kohm  |  Rset kohm")
        print("---------------------------------------------------------------------")
    d = 0.1
    dstep = 0.05
    fnow = startf
    obj = Ltc6992(fnow, d, 0, "any")
    
    pban()
    while fnow < stopf :
        while d < 1 :
            obj.start(fnow, d, 0)
            print(f"{obj.duty:0.2f}  |  ", end='')  
            print(f"{obj.frequency/1.0e3:7.2f}  |   ", end='')
            print(f"{obj.period*1.0e6:7.2f}  |  ", end='')
            print(f"{obj.Rs_top/1.0e3:7.2f}  |  ", end='')
            print(f"{obj.Rs_bot/1.0e3:7.2f}    |  ", end='')
            print(f"{obj.Rs/1.0e3:7.2f}")
            d = d + dstep
        fnow = fnow + fstep
        d=0.1
        if (stopf-fstep+1 > fnow) :
            pban()
    
if __name__ == '__main__' :
    main()

########~~~~~~~~END>  project.py
