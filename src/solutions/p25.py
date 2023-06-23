# ANSWER 4782

"""

Can be solved by hand. See PDF for explanation.

"""


def p25():
    n = 1
    a, b = 1, 1
    while len(str(a)) < 1000:
        a, b = b, a + b
        n += 1
    return n
