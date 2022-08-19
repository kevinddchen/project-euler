# ANSWER 49

"""

Can be solved by hand. See PDF for explanation.

"""


def p63():
    C = 0
    for a in range(1, 10):
        b = 1
        while len(str(a**b)) == b:
            b += 1
        C += b - 1
    return C
