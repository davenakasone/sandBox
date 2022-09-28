"""
reading data to program is important
    use exception handling
    "break" process what you have
    "return" don't want partial read
    "continue" skip over
"""


def main() :
    f_path = '/home/pogo/Desktop/python_math/house_keeping/readMe.txt'
    sf_path = './readMe.txt'

    print("\nlooking at some data reading options")
    print(f"\tvalid path, full:  {f_path}")
    print(f"\tvalid path, short:  {sf_path}")
    print("\tcould also just use file name since in same directory\n")

    myNums = opt1(sf_path)
    print(f"\nopt1,  numbers:  {myNums}")

    myNums = opt2(f_path)
    print(f"\nopt2,  numbers:  {myNums}")

    myNums = opt3(sf_path)
    print(f"\nopt3,  numbers:  {myNums}")

    myNums = opt4(sf_path)
    print(f"\nopt4,  numbers:  {myNums}")

    myNums = opt4("unknown.txt") # produces error
    print(f"opt4,  numbers:  {myNums}")

    myNums = opt5() # take input
    print(f"opt5,  numbers:  {myNums}")



def opt1(any_path) :
    nums_in = []    # start empty
    f_in = open(any_path)
    for line in f_in :
        nums_in.append(float(line))
    f_in.close()
    return nums_in




# prefered, becuase it will still close file if there is an exception
# no need to close()
def opt2(any_path) :
    nums_in = []
    with open(any_path) as f_in :
        for line in f_in :
            nums_in.append(float(line))
    return nums_in



# compress and handle list at same time
def opt3(any_path) :
    with open(any_path) as f_in :
        lines = f_in.readlines()
    nums_in = [float(nn) for nn in lines]
    return nums_in


def opt4(any_path) :
    nums_in = []
    try :
        with open(any_path) as f_in :
            for line in f_in :
                nums_in.append(float(line))
    except FileNotFoundError :
        print("\ncan't find the file")
        return [-999, -999, -999]
    else :
        return nums_in


def opt5() :
    any_path = input("\nenter file path/name:  ")
    data = opt4(any_path)
    return data


if __name__ == '__main__' :
    main()