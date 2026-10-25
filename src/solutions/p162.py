"""

Can be solved by hand. See PDF for explanation.

"""

ANSWER = "3D58725572C62302"


def p162():
    S = sum(15 * 16**n - 43 * 15**n + 41 * 14**n - 13 ** (n + 1) for n in range(2, 16))
    return f"{S:X}"
