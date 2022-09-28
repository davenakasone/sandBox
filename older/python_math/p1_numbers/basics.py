"""
basic use cases
    order PEMDAS: parenthesis, exponents, multiplication/division, addition/subtraction
    integers and floating points are the 2 main types
    always check the type() if not sure
"""

def main() :
    x = 3
    y = 2
    z = x/y
    zz = float(x // y)
    print(f"\n{x} / {y} = {z}")
    print(f"floor division {x}/{y} = {zz}  > rounds down to integer remainder")

    x = -3
    y = 2
    z = x/y
    zz = {x // y}
    print(f"\n{x} / {y} = {z}")
    print(f"floor division {x}/{y} = {zz}  > rounds down to integer remainder negative")

    print("\nthe remainder by modulo is fundamental")
    x = 9
    y = 2
    z = x%y
    print(f"{x} % {y} = {z}")

    print("\npower is taken by ** for squares")
    x = 2
    y = 4
    z = x**y
    print(f"{x}**{y} = {z}")
    w = z**(x/y)
    print(f"{z}**({x}/{y}) = {w}")

    x = 3
    y = 2.5
    print("\nwhat is %d ?  %s" % (x, type(x)))
    print("what is %f ?  %s" % (y, type(y)))
    print("converted to float   :  %d == %f" % (x, float(x)))
    print("converted to integer :  %f == %d" % (y, int(y)))

if __name__ == '__main__' :
    main()

####~~~~END>  basics.py
