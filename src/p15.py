# ANSWER 137846528820

"""

Can be solved by hand. See PDF for explanation.

"""

from math import comb
from time import time


def p15():
    return comb(40, 20)


if __name__ == "__main__":
    time_start = time()
    print(p15())
    print("Time: {0:.3f}".format(time() - time_start))
