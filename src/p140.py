# ANSWER 5673835352990

"""

Can be solved by hand. See PDF for explanation.

"""


def p140():
    x_1, y_1 = 8, 2
    x_2, y_2 = 7, 1

    S = 0
    i = 0
    while i < 30:
        if x_1 < x_2:
            x_1, y_1 = (3 * x_1 + 5 * y_1) // 2, (x_1 + 3 * y_1) // 2
            if x_1 % 5 == 2:
                i += 1
                S += (x_1 - 7) // 5
        else:
            x_2, y_2 = (3 * x_2 + 5 * y_2) // 2, (x_2 + 3 * y_2) // 2
            if x_2 % 5 == 2:
                i += 1
                S += (x_2 - 7) // 5
    return S
