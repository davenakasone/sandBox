"""
cartesian is one of many ways to visualize pair of numbers
each coordinate system has its unique properites
    list [] is like an array, and can be modified, ie .append()
    tuple () is like a const array, and can't be modified
"""

def main () :
    demo_list ()
    demo_tuple ()
    print("lists and tuples can use negative index [-1] refers to last element\n")
    demo_list_itr ()
    demo_tuple_itr ()


####~~~~


def demo_list () :
    slist = [1, 2, 3]
    print(f"\nhere is a simple list:  {slist}")
    print(f"list[0] =  {slist[0]}")
    print(f"list[1] =  {slist[1]}")
    print(f"list[2] =  {slist[2]}")
    print("lists are collection of like data types, index starts @ 0 ...static C array\n")

    print("use an empty []  list if you don't know before ...dynamic C array")
    elist = []
    for ii in range(3) :
        elist.append(ii+4)
        print(f"list[{ii}] =  {elist[ii]}")
    print(f"total list:  {elist}\n")


####~~~~


def demo_tuple () :
    print("tuples are similar to lists but use () brackets and can't be changed")
    stuple = (1, 2, 3)
    print(f"the tuple is:  {stuple}")
    print(f"tuple[0]=  {stuple[0]}")
    print(f"tuple[1]=  {stuple[1]}")
    print(f"tuple[2]=  {stuple[2]}\n")


####~~~~


def demo_list_itr () :
    myList = [1, 2, 3, 4, 5, 6]
    myListMod = []
    print(f"iterate, myList:  {myList}")

    for item in myList :
        myListMod.append(item + 10)
    print(f"myList + 10:      {myListMod}")

    print("\nenumerate() returns index...")
    for ii, item in enumerate(myList) :
        print(f"myList[{ii}] =  {item}")


####~~~~


def demo_tuple_itr () :
    myTup = (11, 22, 33, 44, 55, 66)
    print(f"\niterate, myTup:  {myTup}")
    for item in myTup :
        print(f"myTup + 10:      {item + 10}")

    print("\nenumerate() returns index...")
    for ii, item in enumerate(myTup) :
        print(f"myTup[{ii}] =  {item}")


####~~~~


if __name__ == '__main__' :
    main ()


########~~~~~~~~END>  ex_grouping.py
