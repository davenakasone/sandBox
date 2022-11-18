"""
    hw6, smith chart ch2 and some ch3
"""

import numpy as np
import plotly.graph_objects as go
import math
import cmath
import scipy
import sympy
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
    # p221a()
    # p221b()
    # p221c()
    # p221d()
    # p221e()
    # p223()

    print("\n\n\t\t~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n")
    sys.exit()


####~~~~


def p220() :
    Z_0 = 50.0
    z_L = complex((60.0/50.0), (50.0/50.0))
    pcomplex("zL", z_L)
    G = zload_2_G(z_L)
    swr = G_2_swr(G)
    pcomplex("a) SWR", swr)
    pcomplex("b) G", G)
    y_L = 1/z_L
    Y_L = y_L * (1/Z_0)
    pcomplex("c) y_L", y_L)
    pcomplex("c) Y_L", Y_L)
    expo = complex(0, -2*2*cmath.pi*0.4)
    num = 1 + G * cmath.exp(expo)
    den = 1 - G * cmath.exp(expo)
    Z_in = (num / den) * Z_0
    pcomplex("d) Z_in", Z_in)
    z_in = Z_in / Z_0
    pcomplex("d) z_in", z_in)

    fig = go.Figure()
    fig.add_trace(go.Scattersmith(
        imag=[0, np.imag(z_L)],
        real=[1, np.real(z_L)],
        marker_symbol='x',
        marker_size=10,
        marker_color="green",
        subplot="smith1"
    ))
    fig.add_trace(go.Scattersmith(
        imag=[0, np.imag(y_L)],
        real=[1, np.real(y_L)],
        marker_symbol='diamond',
        marker_size=10,
        marker_color="red",
        subplot="smith1"
    ))
    fig.add_trace(go.Scattersmith(
        imag=[0, np.imag(z_in)],
        real=[1, np.real(z_in)],
        marker_symbol='circle',
        marker_size=10,
        marker_color="blue",
        subplot="smith1"
    ))
    fig.update_smiths(bgcolor="lightgrey")
    fig.show()


####~~~~


def p221a() :
    fig = go.Figure()
    fig.add_trace(go.Scattersmith(
        imag=[0],
        real=[0],
        marker_symbol='x',
        marker_size=20,
        marker_color="green",
        subplot="smith1"
    ))
    fig.update_smiths(bgcolor="lightgrey")
    fig.show()


####~~~~


def p221b() :
    fig = go.Figure()
    fig.add_trace(go.Scattersmith(
        imag=[0],
        real=[99999],
        marker_symbol='x',
        marker_size=20,
        marker_color="green",
        subplot="smith1"
    ))
    fig.update_smiths(bgcolor="lightgrey")
    fig.show()


####~~~~


def p221c() :
    fig = go.Figure()
    fig.add_trace(go.Scattersmith(
        imag=[1],
        real=[0],
        marker_symbol='x',
        marker_size=20,
        marker_color="green",
        subplot="smith1"
    ))
    fig.update_smiths(bgcolor="lightgrey")
    fig.show()


####~~~~


def p221d() :
    fig = go.Figure()
    fig.add_trace(go.Scattersmith(
        imag=[-2/3],
        real=[0],
        marker_symbol='x',
        marker_size=20,
        marker_color="green",
        subplot="smith1"
    ))
    fig.update_smiths(bgcolor="lightgrey")
    fig.show()


####~~~~


def p221e() :
    fig = go.Figure()
    fig.add_trace(go.Scattersmith(
        imag=[2/15],
        real=[0],
        marker_symbol='x',
        marker_size=20,
        marker_color="green",
        subplot="smith1"
    ))
    fig.update_smiths(bgcolor="lightgrey")
    fig.show()


####~~~~


def p223() :
    Z_0 = 50
    swr = 2.5
    G_abs = (swr-1)/(swr+1)
    tht = cmath.pi * 13.0 / 7.0
    G = G_abs * cmath.exp(complex(0.0, tht))
    z_L = (1+G)/(1-G)
    Z_L = Z_0 * z_L
    pcomplex("z_L", z_L)
    pcomplex("Z_L", Z_L)

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
