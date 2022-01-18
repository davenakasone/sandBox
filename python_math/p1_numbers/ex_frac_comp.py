"""
must use the fractions module to handle fractions
    float in operation makes all float
    fraction and integer makes result a fraction

complex numbers index from "j"
    modulo {%} and floor {//} do not apply to complex
"""

from fractions import Fraction

def main() :
    demo_frac()
    demo_comp()


####~~~~


def demo_frac() :
    ff = Fraction(3,4)   # an object is created (numerator, denominator)
    print(f"the fraction is:  {ff}")

    anyInt = 1
    calc = anyInt + ff
    print(f"{anyInt} + {ff} = {calc}    ...int + frac = frac")
    anyFlt = 1.1
    calc = anyFlt + ff
    print(f"{anyFlt} + {ff} = {calc}    ...float makes float")


####~~~~


def demo_comp() :
    zz = 2 + 3j    # define like this, option 1
    print(f"\nzz is:  {zz}  {type(zz)}")
    xx = complex(7, 8)    # define like this, option 2
    print(f"xx is:  {xx}  {type(xx)}")

    yy = zz + xx
    print(f"addition as usual, {zz} + {xx} = {yy}")
    yy = zz - xx
    print(f"subtraction as usual, {zz} - {xx} = {yy}")
    yy = zz * xx
    print(f"multiplication as usual, {zz} * {xx} = {yy}")
    yy = zz / xx
    print(f"division as usual, {zz} / {xx} = {yy}")

    zzr = zz.real
    zzi = zz.imag
    print(f"\ngiven {zz}  , real:  {zzr}  ,  imag:  {zzi}")
    zzc = zz.conjugate()
    print(f"\tconjugate:  {zzc}")
    zzMag = (zz.real**2 + zz.imag**2)**(1/2)
    print(f"\tmagnitude:  {zzMag}   long way")
    zzMag = abs(zz)
    print(f"\tmagnitude:  {zzMag}  using abs()")
    print("\nuse cmath module if you need additional operations\n")


if __name__ == '__main__' :
    main()


########~~~~~~~~END> ex_fractions.py
