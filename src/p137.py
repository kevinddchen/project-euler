# ASNWER 1120149658760

"""

Can be solved by hand. See PDF for explanation.

"""


def p137():
    x, y = 1, 1
    i = 0
    while i < 15:
        x, y = (3 * x + 5 * y) // 2, (x + 3 * y) // 2
        if x % 5 == 1:
            i += 1
    return (x - 1) // 5
