# ANSWER 265695031399260211

"""

Can be solved by hand. See PDF for explanation.

"""


def p577():
    return sum((4115 - n) * (1 + 3 * n) * (2 + 3 * n) * (3 + 3 * n) for n in range(4115)) // 6
