# ANSWER 21384

"""

Can be solved by hand. See PDF for explanation.

"""

from math import comb
from time import time


def p106():
    return sum(comb(12, 2 * k) * comb(2 * k, k) * (k - 1) // (k + 1) for k in range(2, 7)) // 2


if __name__ == "__main__":
    time_start = time()
    print(p106())
    print("Time: {0:.3f}".format(time() - time_start))
