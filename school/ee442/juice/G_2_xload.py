"""
    given reflection coefficient "Gamma"
    finds normalized IMAG part of the load impedance "z_load"
    as x_load
"""

import numpy as np

def G_2_xload(G: complex) -> float :

    num = 2 *  np.imag(G)

    den = (1 - np.real(G))**2 + np.imag(G)**2

    x_load = num / den

    return x_load


########~~~~~~~~END>  G_2_xload.py
