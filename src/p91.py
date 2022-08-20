# ANSWER 14234

from math import gcd


def p91():
    N = 50
    C = 3 * N * N
    for x in range(1, N + 1):
        for y in range(1, N + 1):
            g = gcd(x, y)
            x_g, y_g = x // g, y // g
            C += 2 * min((N - y) // x_g, x // y_g)
    return C
