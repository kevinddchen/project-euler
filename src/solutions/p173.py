# ANSWER 1572729

"""

With a lamina of length x and thinkness y (where 0 < y < x/2), the number of
tiles used is x^2 - (x-2y)^2 = 4y(x-y).

"""


def p173():
    LIMIT = 10**6
    C = 0
    for x in range(3, LIMIT // 4 + 2):
        for y in range(1, (x + 1) // 2):
            if 4 * y * (x - y) > LIMIT:
                break
            C += 1
    return C
