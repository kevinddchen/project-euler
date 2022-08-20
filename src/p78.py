# ANSWER 55374

"""

We can use the exact same methods in problem 76 to solve this one.

"""

from .p76 import partition


def p78():
    n = 100
    while partition(n) % 1000000 != 0:
        n += 1
    return n
