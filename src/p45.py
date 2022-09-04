# ANSWER 1533776805

"""

Can be solved by hand. See PDF for explanation.

"""


def p45():
    x, y = 1, 1
    for _ in range(9):
        x, y = 2 * x + 3 * y, x + 2 * y
    n = (y + 1) // 4
    return n * (2 * n - 1)
