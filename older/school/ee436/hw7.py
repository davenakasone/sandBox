"""
hw7, problem 1, rectangular wave guide
"""
import numpy
import os
import sys

os.system("clear")


cc = 3.0e8
W_min = 75.0e9 # Hz
W_max = 110.0e9 # Hz
wall_a = 0.254/100 # m
wall_b = 0.127/100 # m


def main() :
    Q_rec = W_max - W_min
    Qmn_min = 0
    Qmn_max = 0
    print("\nm  |  n  |  Qmn  GHz         |  (Qmn - Qrec) GHz")
    print("-------------------------------------------------")

    for mm in range(0, 4) :
        for nn in range(0, 4) :
            Qmn = get_wc(mm, nn)
            print(f"{mm}  |  {nn}  |  {Qmn/1e9:12.6f}     |  {(Qmn-Q_rec)/1.0e9:0.3f}")
            if (mm == 1) and (nn == 0) :
                Qmn_min = Qmn
            if (mm == 0) and (nn == 1) :
                Qmn_max = Qmn

    Q_theo = Qmn_max-Qmn_min
    print(f"\nQ_rec = W_max - W_min = {W_max/1e9} - {W_min/1e9} = {Q_rec/1e9:0.4f} GHz   reccomended bandwidth")
    print(f"Q' = Q01 - Q10 = {Qmn_max/1e9:0.4f} - {Qmn_min/1e9:0.4f} = {(Q_theo)/1e9:0.4f} GHz theoretical bandwidth")
    Qdiff = (Q_theo-Q_rec) / Q_theo
    print(f"Qdiff= (Q_theo - Q_rec) / Q_theo = {Qdiff:0.3f} = {100*Qdiff:0.3f} % change")
    print("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n")
    sys.exit()

def get_wc(m: int, n: int) -> float :
    tempc = cc / (2 * numpy.pi)
    tempm = (m * numpy.pi / wall_a)**2
    tempn = (n * numpy.pi / wall_b)**2
    return (tempc * numpy.sqrt(tempm + tempn))


####~~~~


if __name__ == '__main__' :
    main()

#########~~~~~~~~END>  hw7.py
