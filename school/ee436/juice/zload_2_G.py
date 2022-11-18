"""
    given normalized load impedance "z_load"
    finds reflection coefficient "Gamma"
"""

import numpy as np

def zload_2_G(z_load: complex) -> complex :

    num = z_load - 1

    den = z_load + 1

    Gamma = num / den

    return Gamma


########~~~~~~~~END>  zload_2_G.py
