"""
basic matplotlib
"""

import matplotlib.pyplot as plt
import numpy as np


def main () :
    demo_basic ()


####~~~~


def demo_basic () :
    #x_nums = [1, 2, 3]
    #y_nums = [2, 4, 6]
    plt.style.use('_mpl-gallery')
    x = np.linspace(0, 10, 100)
    y = 4 + 2 * np.sin(2 * x)
    ax = plt.subplots()
    ax.plot(x, y, linewidth=2.0)
    ax.set(xlim=(0, 8), xticks=np.arange(1, 8),
       ylim=(0, 8), yticks=np.arange(1, 8))

    plt.show()


####~~~~


if __name__ == '__main__' :
    main ()

########~~~~~~~~END>  ex_plot.py
