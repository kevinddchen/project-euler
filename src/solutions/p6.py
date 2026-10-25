"""

Can be solved by hand. See PDF for explanation.

"""

ANSWER = 25164150


def p6():
    return sum(x for x in range(101)) ** 2 - sum(x * x for x in range(101))
