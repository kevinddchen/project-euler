# ANSWER 31875000

"""

Can be solved by hand. See PDF for explanation.

"""

from math import gcd, isqrt
from time import time


def p9():
    # Euclid's formula for generating Pythagorean triples.
    # a+b+c = 2km(m+n) = 1000, so stop m at sqrt(500).
    for m in range(2, isqrt(500) + 1):
        # m, n must have opposite parity
        if m % 2 == 0:
            n_start = 1
        else:
            n_start = 2

        for n in range(n_start, m, 2):
            if gcd(m, n) == 1:
                a = m * m - n * n
                b = 2 * m * n
                c = m * m + n * n
                if 1000 % (a + b + c) == 0:
                    return a * b * c * (1000 // (a + b + c)) ** 3


if __name__ == "__main__":
    time_start = time()
    print(p9())
    print("Time: {0:.3f}".format(time() - time_start))
