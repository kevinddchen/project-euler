# ANSWER 669171001

"""

Can be solved by hand. See PDF for explanation.

"""


def p28():
    return sum(4 * x * x - 6 * x + 6 for x in range(3, 1002, 2)) + 1
