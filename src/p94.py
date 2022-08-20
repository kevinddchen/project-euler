# ANSWER 518408346

"""

Can be solved by hand. See PDF for explanation.

"""


def p94():
    LIMIT = 10**9
    S = 0

    x, y = 2, 1
    while True:
        x, y = 2 * x + 3 * y, x + 2 * y
        if x % 3 == 2:
            delta = 0
        else:
            delta = 1
        p = 2 * (x + 2 * delta - 1)
        if p > LIMIT:
            break
        S += p
    return S
