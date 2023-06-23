# ANSWER 1118049290473932

"""

Can be solved by hand. See PDF for explanation.

"""


def p138():
    x, y = 2, 1
    S = 0
    for _ in range(12):
        x, y = 9 * x + 20 * y, 4 * x + 9 * y
        S += y
    return S
