"""
    when python script runs, it gets "__name__" variable
    control execution if program is part of others or stand-alone
"""


def fact(nn) :
    pp = 1
    for ii in range (1, nn+1) :
        pp = pp * ii
    return pp

print(__name__)

if __name__ == '__main__' :
    nn = int(input("enter an integer to get factiorial:  "))
    ff = fact(nn)
    print(f"factorial of:  {nn}  is   {ff}\n")
