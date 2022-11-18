"""
    given reflection coefficient gamma "G"
    finds standing wave ratio "SWR"
"""

import numpy as np

def G_2_swr(G: complex) -> complex :

    num = 1 + np.abs(G)

    den = 1 - np.abs(G)

    swr = num / den

    return swr


########~~~~~~~~END>  G_2_swr.py
