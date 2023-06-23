# ANSWER 149253

from mathfuncs import is_prime

from .p129 import A


def p130():
    S = 0
    i = 0

    n = 2
    while i < 25:
        n += 1
        if n % 2 == 0 or n % 5 == 0 or is_prime(n):
            continue
        if (n - 1) % A(n) == 0:
            S += n
            i += 1
    return S
