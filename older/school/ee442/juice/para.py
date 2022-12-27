"""
    parallel passive component
    remember that series capcitors are like parallel resistors

    A||B = [(1/A) + (1/B)]^(-1) = (AB) / (A+B)
"""


def para(A: complex, B: complex) -> complex :
    return ((A*B)/(A+B))


#########~~~~~~~~END>  para.py
