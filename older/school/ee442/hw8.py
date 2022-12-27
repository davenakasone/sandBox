"""
    ee442, hw8
    oscillator [0:5] V, f = 100 kHz, T =
"""
import os
import sys
import numpy

def main() -> None :
    # given
    D: float          = 0.95
    f_osc: float      = 100.0e3
    T_osc: float      = 1 / f_osc
    V_osc_min: float  = 0.0
    V_osc_max: float  = 5.0
    V_source: float   = 5.0 
    V_ramp_min: float = 0.0
    V_ramp_max: float = 4.0
    Ndivz: int        = 8
    os.system("clear")
    
    # detrermine the pinout for the LTC6992-1
    print("\n1) Design an oscillator (pick an IC):")
    print(f"\tf_osc = {f_osc/1.0e3:0.1f} kHz")                     
    print(f"\tT_osc = {T_osc*1.0e6:0.1f} us")      
    print(f"\tD = {D*100:0.1f} %")                    
    print(f"\tV_osc = [ {V_osc_min:0.1f} : {V_osc_max:0.1f} ] V")    
    print(f"\tNdiv[{Ndivz}] = [ ", end='')                           # Ndiv has several options, pow(4,x)
    N_div_v: int = [] # gnd, float, to Vcc
    for xx in range(0, Ndivz) :
        N_div_v.append(numpy.power(4, xx))
        if xx == Ndivz-1 :
            print(f"{N_div_v[xx]} ]")
        else :
            print(f"{N_div_v[xx]}", end=', ')
    V_set: float        = 1.0                                                       # V_set is usually 1V
    R_div_top: int      = 976                                                       # resistor voltage divider, sets V_div from V_source, top
    R_div_bottom: int   = 102                                                       # resistor voltage divider, sets V_div from V_source, bottom
    N_div: int          = N_div_v[1]                                                # the Ndiv reccomended in data sheet
    V_div: float        = V_source * (R_div_bottom / (R_div_top + R_div_bottom))    # ensure V_div is in data sheet range
    R_set: float        = ((1.0e6) * (50.0e3)) / (N_div * f_osc)                    # R_set according to data sheet
    f_osc: float        = (1.0e6 / N_div) * (50.0e3 / R_set)                        # check f_osc with datasheet equation
    R_set_bottom: float = 108.0e3                                                   # resistor voltage divider, sets V_mod from V_set, bottom
    R_set_top: float    = 17.0e3                                                    # resistor voltage divider, sets V_mod from V_set, top
    V_mod: float        = V_set * (R_set_bottom / (R_set_bottom + R_set_top))       # V_mod sets duty cycle (or clamps)
    De: float           = (V_mod / (0.8 * V_set)) - (1/8)                           # expected duty cycle
    print(f"\n\tRdiv_top= {R_div_top} ,  Rdiv_bottom= {R_div_bottom}  , Vdiv/Vs= {V_div/V_source:0.5f} ...Ndiv={N_div}, polarity 0")
    print(f"\tf_osc = {f_osc/1.0e3:0.1f} kHz")
    print(f"\tR_set= {R_set/1e3:0.1f} k, Rset_top = {R_set_top/1.0e3:0.1f} k, Rset_bottom= {R_set_bottom/1.0e3:0.1f} k")
    print(f"\tV_mod= {V_mod:0.3f} V  -->  D= {De*100:0.1f} %")

    print("\n2) use the oscillator with another IC to make a ramp generator:")
    print(f"\tV_source = {V_source:0.1f} V")
    print(f"\tV_ramp = [ {V_ramp_min:0.1f} : {V_ramp_max:0.3f} ] V")
    V_ref: float = 1.25
    V_diff: float = V_source - V_ref
    R_pmos: float = 2.1e3
    I_ramp = V_ref / R_pmos
    C: float = 1.0e-9
    dV_dt = I_ramp/C
    print(f"\tC = {C*1.0e9:0.1f} nF")
    print(f"\tR = {R_pmos/1.0e3:0.1f} k")
    print(f"\tdV / dt = {dV_dt/1.0e6:0.3f}   V per us")
    print("\tand just change the resistors on the oscillator to invert the duty cycle")

    print("\n\n~ ~ ~ PROGRAM COMPELTE ~ ~ ~\n\n")
    sys.exit()

if __name__ == '__main__' :
    main()

########~~~~~~~~END>  hw8.py
