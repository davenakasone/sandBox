"""
    calculations for the LTC-6692 oscillator
        - assumes you keep Ndiv @ 4 so f[15.63kHz to 250kHz]
        - assumes polarity 0
        - Ndiv_top "R1" == 976 ohm, Ndiv_bottom "R2" = 102 ohm 
        
    read the data sheet:
    https://www.analog.com/media/en/technical-documentation/data-sheets/ltc6992-1-6992-2-6992-3-6992-4.pdf
"""

import sys
import os

ndiv = 4
FAILURE = "selection does not match device specifications"


def main() :
    os.system("clear")
    # pick 1 function to call, comment out the other :
    
    #osc_from_f_and_D(100.0e3, 0.3)        # you have a target        (frequency, duty cycle)
    #osc_from_resistors(60.0e3, 90.0e3)    # you see a schematic with (Rset top, Rset bottom)
    osc_from_resistors(90.0e3, 110.0e3)
    osc_from_resistors(60.0e3, 18.0e3)
    
    print("\n\n~ ~ ~ PROGRAM COMPELTE ~ ~ ~\n\n")
    sys.exit()

def osc_from_resistors(Rs_t, Rs_b) :
    Rs = Rs_t + Rs_b
    frq = 50.0e9 / (ndiv * Rs)
    T = 1 / frq
    vmod = Rs_b / (Rs_b + Rs_t)
    dty = (vmod / 0.8) - (1/8)
    print(f"\nthe oberseved oscillator has the following properties, ndiv={ndiv} :\n")
    print(f"f            = {frq/1.0e3:0.1f} kHz")
    print(f"T            = {T*1.0e6:0.2f} us")
    print(f"D            = {dty*100:0.2f} %")
    print(f"Rset         = {Rs/1.0e3:0.1f} kohm")
    print(f"Rset, top    = {Rs_t/1.0e3:0.1f} kohm")
    print(f"Rset, bottom = {Rs_b/1.0e3:0.1f} kohm")
    print("\nD     |   f  kHz  |  T  us     | top  kohm |  bot  kohm  |  Rset kohm")
    print("---------------------------------------------------------------------")
    dstep = 0.05
    d = dstep
    while d < 1 :
        f, T, D, rs, rst, rsb = helper(frq, d)
        print(f"{D:0.2f}  |  ", end='')  
        print(f"{f/1.0e3:7.2f}  |   ", end='')
        print(f"{T*1.0e6:7.2f}  |  ", end='')
        print(f"{rst/1.0e3:7.2f}  |  ", end='')
        print(f"{rsb/1.0e3:7.2f}    |  ", end='')
        print(f"{rs/1.0e3:7.2f}")
        d = d + dstep
    
def osc_from_f_and_D(frq: float, dty: float) -> None :
    if (frq < 15.63e3) or (frq > 250.0e3) or (dty < 0.0) or (dty > 1.0) :
        print(f"{FAILURE}")
        return
    f, T, D, rs, rst, rsb = helper(frq, dty)
    print(f"\noscillator, given f={f/1.0e3:0.1f} kHz  ,  D={dty:0.2f}  , ndiv={ndiv}:\n")
    print(f"f            = {f/1.0e3:0.1f} kHz")
    print(f"T            = {T*1.0e6:0.2f} us")
    print(f"D            = {D*100:0.2f} %")
    print(f"Rset         = {rs/1.0e3:0.1f} kohm")
    print(f"Rset, top    = {rst/1.0e3:0.1f} kohm")
    print(f"Rset, bottom = {rsb/1.0e3:0.1f} kohm")
    print("\nD     |   f  kHz  |  T  us     | top  kohm |  bot  kohm  |  Rset kohm")
    print("---------------------------------------------------------------------")
    dstep = 0.05
    d = dstep
    while d < 1 :
        f, T, D, rs, rst, rsb = helper(f, d)
        print(f"{D:0.2f}  |  ", end='')  
        print(f"{f/1.0e3:7.2f}  |   ", end='')
        print(f"{T*1.0e6:7.2f}  |  ", end='')
        print(f"{rst/1.0e3:7.2f}  |  ", end='')
        print(f"{rsb/1.0e3:7.2f}    |  ", end='')
        print(f"{rs/1.0e3:7.2f}")
        d = d + dstep
    
def helper(f, D) :
    T = 1 / f
    rs = 50.0e9 / (ndiv * f)     
    rsb = rs * (D + (1/8)) * 0.8
    rst = rs - rsb
    vmod = rsb / (rsb + rst)
    DD = (vmod / 0.8) - (1/8)
    return f, T, DD, rs, rst, rsb
    
if __name__ == '__main__' :
    main()

####~~~~END>  osc_ltc6692.py
