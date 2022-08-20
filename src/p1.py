# ANSWER 233168

"""

Can be solved by hand. See PDF for explanation.

"""


def p1():
    return sum(x for x in range(1000) if x % 3 == 0 or x % 5 == 0)
