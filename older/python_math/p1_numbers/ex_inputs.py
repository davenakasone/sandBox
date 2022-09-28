"""
everything is a string in python
single or double quotes don't matter
you have to convert inputs to float or integer

use a definite conversion technique...not all are guarunteed
"""

from decimal import DivisionByZero
from fractions import Fraction
import math
from multiprocessing.dummy import Value


def main() :
    demo_inputs()
    demo_strings()
    demo_conv()
    demo_bad_con()
    demo_bad_frac()
    demo_bad_comp()


####~~~~


def demo_inputs() :
    aa = input("enter something: ")  # enter some digitis to see how it is handleded
    print(f"you entered:  {aa}")
    print(f" this is a :  {type(aa)}")
    print("...everything is a string\n")


####~~~~


def demo_strings() :
    strA = "any string"
    strB = 'any string'
    print(f"string 2x quote:  {strA}")
    print(f"string 2x quote:  {strB}")
    print("single or double quotes are the same...\n")


####~~~~


def demo_conv() :
    bb = '5'
    print(f"bb = {bb}  ,  type:  {type(bb)}")
    print("must convert to int() or float() to work with")
    bbi = int(bb)
    bbf = float(bb)
    print(f"\tbbi =  {bbi}  ,  type:  {type(bbi)}")
    print(f"\tbbf =  {bbf}  ,  type:  {type(bbf)}\n")


####~~~~


def demo_bad_con() :
    xx = 4.99999
    yy = 99
    print(f"xx =  {xx}  ,  type:  {type(xx)}   ...can't int() to float")
    if (xx.is_integer()) :
        yy = xx
    else :
        yy = int(math.floor(xx))
    print (f"yy =  {yy}  ,  type;  {type(yy)}\n")


####~~~~


def demo_bad_frac() :
    ff = Fraction(3, 4)
    try :
        ff = Fraction(3, 0)
    except ZeroDivisionError:
        print("can't divide by 0\n")
    else :
        print("all is well\n")

####~~~~


def demo_bad_comp() :
    cn = complex(2, 3)
    try :
        cn = "2 + 3j"
        cn = complex(cn)
    except ValueError :
        print("bad complex format\n")
    else :
        print("all is well\n")


if __name__ == '__main__' :
    main()


########~~~~~~~~END>  ex_inputs.py
