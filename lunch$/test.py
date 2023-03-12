""" 
    test the "ffun" package
    use interactive mode, ie:
    
        $ python3 -i test.py
"""

import os
import sys

from ffuns import lumpsum_pv # t1
from ffuns import lumpsum_fv # t2
from ffuns import lumpsum_n  # t3
from ffuns import lumpsum_r  # t4
from ffuns import annuity_pv # t5
from ffuns import annuity_fv # t6

os.system("clear")


def stop() :
    print("\n\n\t\t~ ~ ~ COMPLETE ~ ~ ~\n\n")
    sys.exit()
    
def t1(r= 0.05, n=1.0, fv=105.0) -> None :
    print(f"r  = {r*100:0.3f} %")
    print(f"n  = {n:0.1f}")
    print(f"fv = {fv:,.2f}")
    print("--> ffun --> lumpsum_pv()")
    pv = lumpsum_pv(r, n, fv)
    print(f"pv = {pv:,.2f}")

def t2(r= 0.05, n=1.0, pv=100.0) -> None :
    print(f"r  = {r*100:0.3f} %")
    print(f"n  = {n:0.1f}")
    print(f"pv = {pv:,.2f}")
    print("--> ffun --> lumpsum_fv()")
    pv = lumpsum_fv(r, n, pv)
    print(f"fv = {pv:,.2f}")

def t3(r=0.05, pv=100.0, fv=105.0) -> None :
    print(f"r  = {r*100:0.3f} %")
    print(f"pv  = {pv:,.2f}")
    print(f"fv = {fv:,.2f}")
    print("--> ffun --> lumpsum_n()")
    n = lumpsum_n(r, pv, fv)
    print(f"n = {n:0.1f}")

def t4(n=1.0, pv=100.0, fv=105.0) -> None :
    print(f"n  = {n:0.1f}")
    print(f"pv  = {pv:,.2f}")
    print(f"fv = {fv:,.2f}")
    print("--> ffun --> lumpsum_r()")
    r = lumpsum_r(n, pv, fv)
    print(f"r = {r*100:0.3f} %")

def t5(pmt=1.0e3, n=10.0, r=0.077) -> None :
    print(f"pmt  = {pmt:,.2f}")
    print(f"n    = {n:0.1f}")
    print(f"r    = {r*100:0.3f} %")
    print("--> ffun --> annuity_pv()")
    pv = annuity_pv(pmt, n, r)
    print(f"pv = {pv:,.2f}")
    test = 0
    for ii in range(0, int(n)) :
        test += lumpsum_pv(r, ii+1, pmt)
    if abs(test - pv) < 0.01 :
        print(f"confirmed ...  {test:,.2f}")
    else :
        print("...FAILED")

def t6(pmt=1.0e3, n=5.0, r=0.05) -> None :
    print(f"pmt  = {pmt:,.2f}")
    print(f"n    = {n:0.1f}")
    print(f"r    = {r*100:0.3f} %")
    print("--> ffun --> annuity_fv()")
    fv = annuity_fv(pmt, n, r)
    print(f"pv = {fv:,.2f}")
    test = 0
    for ii in range(0, int(n)) :
        test += lumpsum_fv(r, ii, pmt)
    if abs(test - fv) < 0.01 :
        print(f"confirmed ...  {test:,.2f}")
    else :
        print("...FAILED")
        
def tall() -> None :
    print("\n")
    t1()
    print("\n")
    t2()
    print("\n")
    t3()
    print("\n")
    t4()
    print("\n")
    t5()
    print("\n")
    t6()
    stop()


########~~~~~~~~END>  test.py
