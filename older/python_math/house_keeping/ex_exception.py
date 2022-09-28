"""
exceptions need good handling in any language
statements in "try" block that raise an exception present type to "except" block
if caught, program resumes in except block
otherwise, the program halts

be familiar with all the possible exceptions
use "else" block to specify no exception
"""

def main() :
    try :
        xx = int('1.1')
    except ValueError :
        print("failed to convert to an integer")

    print("\ncall to divide by 0...")
    recip(0)

    print("\ncall with bad type...")
    recip('1')

    print("\ncall correct...")
    recip(4)




def recip(nn) :
    try :
        nnn = 1 / nn
    except TypeError :
        print("type error")
    except ZeroDivisionError :
        print("dividing by 0 is bad")
    else :
        print(f"reciprocal of {nn} is {nnn}")




if __name__ == '__main__' :
    main()
