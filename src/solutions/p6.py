# ANSWER 25164150

"""

Can be solved by hand. See PDF for explanation.

"""


def p6():
    return sum(x for x in range(101)) ** 2 - sum(x * x for x in range(101))
