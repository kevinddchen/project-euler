# ANSWER 190569292

"""

This problem is asking for the integer partition of 100. This can be calculated
recursively using the pentagonal number theorem.

"""

from functools import cache


def pent(n):
    return n * (3 * n - 1) // 2


def alternating():
    """Generate sequence 1, -1, 2, -2, 3, -3, ..."""
    i = 1
    while True:
        yield i
        yield -i
        i += 1


@cache
def partition(n):
    # also used in Problem 78
    if n == 0:
        return 1
    S = 0
    for k in alternating():
        g_k = pent(k)
        if g_k > n:
            break
        S += partition(n - g_k) * (-1 if k % 2 == 0 else 1)
    return S


def p76():
    return partition(100)
