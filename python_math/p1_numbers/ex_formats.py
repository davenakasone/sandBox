"""
some use cases of formating
    old school
    .format()   
    f-string
"""


def main() :
    mult_tab(9)

####~~~~


def mult_tab(numIn) :
    for ii in range(0, 11) :
        print(f"{numIn:2d} X {ii:2d} =  {numIn*ii:2d}")

####~~~~


if __name__ == '__main__' :
    main()


########~~~~~~~~END> ex_formats.py
