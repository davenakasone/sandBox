"""
    laboratory 24, linear thermal expansion
"""


def main() :
    #pre4()
    pre5()

def pre4() :
    L0 = 1.117
    T0 = 22.0
    T1 = 275.0
    alpha = 16.8e-6
    dT = T1 - T0
    L1 = alpha * L0 * dT + L0
    dL = L1 - L0
    print(f"L1=  {L1:0.6f} m  ... expans {dL*1e3:0.3f} mm")

def pre5() :
    alpha = 11.4e-6
    L0 = 10.0
    T0 = 20.0
    T1 = 40.0
    dT = T1 - T0
    dL = alpha * L0 * dT
    print(f"dL=  {dL*1e3:0.3f} mm")



####~~~~


if __name__ == '__main__' :
    main()


########~~~~~~~~END>  lab24.py
