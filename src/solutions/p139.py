# ANSWER 10057761

"""

Can be solved by hand. See PDF for explanation.

"""


def p139():
    LIMIT = 10**8
    C = 0

    x, y = 1, 1
    while x + y < LIMIT:
        x, y = 3 * x + 4 * y, 2 * x + 3 * y
        C += LIMIT // (x + y)

    return C
