# ANSWER 333082500

"""

Can be solved by hand. See PDF for explanation.

"""


def p120():
    return sum(a * a - (1 if a % 2 == 1 else 2) * a for a in range(3, 1001))
