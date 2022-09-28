"""
using some code to get a factor

"""

def main() :
    low = 1
    high = 4
    demo_range(low, high)

    a = 4
    b = 1024
    rezult = is_a_factor(a, b)
    print(f"<{a}>  factor of  <{b}> ?   {rezult}\n")

    facMe = 25
    demo_factor(facMe)


####~~~~


def demo_range(ll, ul) :
    print(f"using range()  ,  ll:  {ll}  ul:  {ul}")
    for ii in range(ll, ul) :
        print(ii)
    print("range() starts at integer given and stops before upper...integers only")
    print(f"range() given only 1 arg,  {ul}  assumes start at 0")
    for ii in range(ul) :
        print(ii)
    print("use range() with 3 args [start, stop, step], here (1, 10, 2)")
    for ii in range(1, 10, 2) :
        print(ii)
    print("\n")

####~~~~


def is_a_factor(aa, bb) :
    if aa==0 or bb == 0 : return False

    if (bb % aa == 0) :
        return True
    else :
        return False


####~~~~


def demo_factor(fak) :
    if not type(fak) == int : print("need an integer")
    if fak <= 0 : print ("must be positive")
    for ii in range(1, fak+1) :
        if fak % ii == 0 :
            print(f"factor of {fak}:  {ii}")


####~~~~


if __name__ == '__main__' :
    main()


########~~~~~~~~END>  ex_factors.py
