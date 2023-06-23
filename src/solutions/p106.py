# ANSWER 21384

"""

Can be solved by hand. See PDF for explanation.

"""

from math import comb


def p106():
    return sum(comb(12, 2 * k) * comb(2 * k, k) * (k - 1) // (k + 1) for k in range(2, 7)) // 2
