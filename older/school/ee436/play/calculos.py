"""
    try some python stuff
    most integrals can't be solved analytically...know which case you are in
    - try in sympy to solve first
    ...define stuff about your symbols if you know in advance...(real, positive, ...)
    use Rational when you have it, otherwise floats
    
"""

import math
import cmath
import mpmath
import numpy
import scipy # has a lot of math capabilities built on the above
import sympy # good for non-analyticals
import os


def main() :
    os.system("clear")
    
    f = lambda x:numpy.sin(x)
    
    print("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n")


def ex_analytic():
    x = sympy.symbols('x', real=True)
    f = sympy.sin()
####~~~~


if __name__ == '__main__' :
    main()


########~~~~~~~~END>  calculos.py
