# ANSWER 104743

from mathfuncs import is_prime


def p7():
    n, i = 1, 1
    while i < 10001:
        n += 2
        if is_prime(n):
            i += 1
    return n
