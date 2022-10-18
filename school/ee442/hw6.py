"""
    ch2 is the smith chart
    matlab was failing, so see how this works
"""

import numpy as np
import plotly.graph_objects as go

import os
import sys

os.system("clear")

from juice.zload_2_G import zload_2_G
from juice.G_2_rload import G_2_rload
from juice.G_2_xload import G_2_xload
from juice.G_2_zload import G_2_zload
from juice.G_2_swr import G_2_swr
from juice.pcomplex import pcomplex


####~~~~


def main() :

    p220()
    
    print("\n\n\t\t~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n")
    sys.exit()


####~~~~


def p220() :
    z_L = complex((60.0/50.0), (50.0/50.0))
    pcomplex("zL", z_L)
    G = zload_2_G(z_L)
    swr = G_2_swr(G)
    pcomplex("a) SWR", swr)
    pcomplex("b) G", G)

    fig = go.Figure()
    fig.add_trace(go.Scattersmith(
        imag=[0, np.imag(z_L)],
        real=[1, np.real(z_L)],
        marker_symbol='x',
        marker_size=10,
        marker_color="green",
        subplot="smith1"
    ))
    fig.update_smiths(bgcolor="lightgrey")
    fig.show()





####~~~~


def ex1() :
    Z_0 = 100 + 0j
    Z_line = 40 + 70j
    z_load = Z_line / Z_0
    pcomplex("z_load", z_load)

    G = zload_2_G(z_load)
    pcomplex("Gamma", G)
    check = G_2_zload(G)
    checkk = complex(G_2_rload(G), G_2_xload(G))
    pcomplex("zload back", check)
    pcomplex("zload parts", checkk)
    

####~~~~


def ex2() :
    fig = go.Figure(go.Scattersmith(imag=[0.5, 1, 2, 30], real=[0.5, 1, 20, 3]))
    fig.show()

####~~~~

def ex3() :
    fig = go.Figure()

    fig.add_trace(go.Scattersmith(
        imag=[1],
        real=[1],
        marker_symbol='x',
        marker_size=30,
        marker_color="green",
        subplot="smith1"
    ))

    fig.add_trace(go.Scattersmith(
        imag=[1],
        real=[1],
        marker_symbol='x',
        marker_size=30,
        marker_color="pink",
        subplot="smith2"
    ))

    fig.update_layout(
        smith=dict(
            realaxis_gridcolor='red',
            imaginaryaxis_gridcolor='blue',
            domain=dict(x=[0,0.45])
        ),
        smith2=dict(
            realaxis_gridcolor='blue',
            imaginaryaxis_gridcolor='red',
            domain=dict(x=[0.55,1])
        )
    )

    fig.update_smiths(bgcolor="lightgrey")

    fig.show()


####~~~~


if __name__ == '__main__' :
    main()


#########~~~~~~~~END>  hw6.py
