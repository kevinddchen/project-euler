# ANSWER 40886

"""

Use Newton's method to generate a good rational approximation of the the
square root (error < 1e-110). Then, use long division to get the digits.

"""

from math import isqrt
from time import time


def gen_sqrt(p):
    """Rational approximation from Newton's method."""
    a, b = isqrt(p), 1
    while True:
        yield a, b
        a, b = a * a + p * b * b, 2 * a * b


def error(p, a, b):
    """Gives error between p and (a/b)^2."""
    return abs(a * a - p * b * b) / (1.0 * b * b)


def long_division(a, b):
    """Iterates through decimal digits from long division."""
    while True:
        c = a // b
        yield c
        a -= c * b
        a *= 10


def p80():
    S = 0
    ERROR_THRESHOLD = 1e-110
    for i in range(2, 100):
        # if square, skip
        if isqrt(i) ** 2 == i:
            continue
        # generate good decimal approximation of sqrt(i)
        G = gen_sqrt(i)
        a, b = next(G)
        while error(i, a, b) > ERROR_THRESHOLD:
            a, b = next(G)
        # long division to get digits
        H = long_division(a, b)
        for j in range(100):
            S += next(H)
    return S


if __name__ == "__main__":
    time_start = time()
    print(p80())
    print("Time: {0:.3f}".format(time() - time_start))
