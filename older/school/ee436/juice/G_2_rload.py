"""
    given reflection coefficient "Gamma"
    finds normalized REAL part of the load impedance "z_load"
    as r_load
"""

import numpy as np

def G_2_rload(G: complex) -> float :

    num = 1 - np.real(G)**2 - np.imag(G)**2

    den = (1 - np.real(G))**2 + np.imag(G)**2

    r_load = (num / den)

    return r_load


########~~~~~~~~END>  G_2_rload.py
