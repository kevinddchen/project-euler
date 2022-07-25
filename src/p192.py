# ANSWER 57060635927998347

"""

The best rational approximations are easily generated from the continued
fraction. See https://en.wikipedia.org/wiki/Continued_fraction for more info.

The difficult part actually comes from applying rule (3) in the "Best rational
approximations" section of the Wiki page. Mathematically, we have two candidate
rational approximations h/k and h'/k' and we want the one with minimal
difference with sqrt(n). However, by the nature of these best rational
approximations, the differences |sqrt(n) - h/k| and |sqrt(n) - h'/k'| are
extremely small numbers (on the order of ~10^(-24)) and so the differences will
be zero due to precision lost in manipulating the floating-point values.

Instead, we can exploit the fact that the even convergents approach sqrt(n) from
below, and the odd convergense approach sqrt(n) from above. In other words,
sqrt(n) - h/k and sqrt(n) - h'/k' will have opposite sign. If
sqrt(n) - h/k < 0, then the condition

    |sqrt(n) - h'/k'| < |sqrt(n) - h/k|

is equivalent to

    h'k + k'h > 2kk'sqrt(n)

Squaring both sides, we can exploit Python's handling of arbitrarily large
integers to test which difference is larger.

"""

from math import isqrt
from time import time

from .p64 import continued_fraction_of_sqrt


def best_rational_approximation(n, bound):
    """Returns tuple (h, k) where h/k ~ sqrt(n) is the best approximation for
    all k <= bound. n must be non-square."""

    # from continued fraction sequence, generate rational approximations h/k
    cont_frac = continued_fraction_of_sqrt(n)
    h, old_h = 1, 0
    k, old_k = 0, 1
    greater_than = True  # True if h/k > sqrt(n)
    while True:
        a = next(cont_frac)
        new_k = a * k + old_k
        if new_k > bound:
            break
        h, old_h = a * h + old_h, h
        k, old_k = new_k, k
        greater_than = not greater_than

    # find best rational approximation under the bound
    b = (bound - old_k) // k
    new_h, new_k = b * h + old_h, b * k + old_k
    if b > a // 2:
        return new_h, new_k
    if b == a // 2 and a % 2 == 0:
        # comparing |sqrt(n) - new_h/new_k| and |sqrt(n) - h/k|.
        # see explanation above.
        condition = (new_h * k + h * new_k) ** 2 > 4 * n * (new_k * k) ** 2
        if (greater_than and condition) or ((not greater_than) and (not condition)):
            return new_h, new_k
    return h, k


def p192():
    max_n = 100_000
    bound = 1_000_000_000_000

    S = 0
    for n in range(2, max_n + 1):

        root = isqrt(n)
        if root * root == n:
            continue

        _, k = best_rational_approximation(n, bound)
        S += k

    return S


if __name__ == "__main__":
    time_start = time()
    print(p192())
    print("Time: {0:.3f}".format(time() - time_start))
