# ANSWER 837799

"""

A useful programming technique in dynamical programming is memoization. In a
process where we anticipate that a function would be called multiple times with
the same input, it is often more efficient to remember a table of input-output
values, which we should consult first. In Python, this can be easily done using
the @cache decorator.

"""

from functools import cache


@cache
def checkchain(x):
    """Returns chain length for x."""
    if x == 1:
        return 1
    elif x % 2 == 0:
        return checkchain(x // 2) + 1
    else:
        return checkchain(3 * x + 1) + 1


def p14():
    return max((checkchain(x), x) for x in range(1, 1000000))[1]
