"""
    given reflection coefficient "Gamma"
    finds normalized load impedance "z_load"
"""

import numpy as np

def G_2_zload(G: complex) -> complex :

    num = 1 + G

    den = 1 - G

    z_load = num / den
    
    return z_load


########~~~~~~~~END>  G_2_zload.py
