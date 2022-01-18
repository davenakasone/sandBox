"""
lots of times, it is good to have a functiont can return more than 1 value
several methods are availible...dictionary is the "nicest"
"""


def main() :
    xx = 0
    yy = 0
    xx, yy = fun_quick(xx, yy)
    print("\nstandard return, order-dependent")
    print(f"xx=  {xx}  ,  yy=  {yy}")

    zz = fun_tup(xx, yy)
    print("\ntuple return, indexed to values")
    print(f"xx=  {zz[0]}  ,  yy=  {zz[1]}")

    dick = fun_dic(xx, yy)
    print("\nreturning a dictionary")
    print(f"xx=  {dick['xx']}  ,  yy =  {dick['yy']}")

    print("\n a practical example of donations:")
    donations = [400, 500, 100, 20, 732, 410, 987, 320]
    result = find_range(donations)
    print(f"given donations:  {donations}")
    print(f"smallest:  {result['lowest']}  ,  largest:  {result['highest']}  ,  range:  {result['range']}")


def fun_quick(aa, bb) :
    aa = 1
    bb = 2
    return aa, bb


def fun_tup(aa, bb) :
    aa = 3
    bb = 4
    return aa, bb


def fun_dic(aa, bb) :
    aa = 5
    bb = 6
    return {'xx': aa, 'yy': bb}

def find_range(arg_in) :
    lowest = min(arg_in)
    highest = max(arg_in)
    spread = highest - lowest
    return {'lowest': lowest, 'highest': highest, 'range': spread}


if __name__ == '__main__' :
    main()


########~~~~~~~~END>  ex_multi_return.py
