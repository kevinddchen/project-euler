# ANSWER 4613732

"""

Can be solved by hand. See PDF for explanation.

"""


def p2():
    S = 0
    a, b = 0, 1
    while a < 4000000:
        if a % 2 == 0:
            S += a
        a, b = b, a + b
    return S
