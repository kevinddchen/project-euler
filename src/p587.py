# ANSWER 2240

"""

If the circle has unit radius, then the L-section has area 1 - pi/4. If the
corner of the L-section is at the origin, then the straight line is given by the
equation y = nx for a particular value of n. The intersect of this straight
line and the circle occurs at the x-value,

    x_n = (n+1-sqrt(2n)) / (n^2+1)

Then using calculus, the area of the concave
triangle is,

    int_0^{x_n} dx (1 - sqrt(1 - (x-1)^2) - nx)
    = 0.5 ( (1-x_n) sqrt(1 - (1 - x_n)^2) + arcsin(1-x_n) - n x_n^2 + 2 x_n - pi/2 )

We iterate through values of n until the area is small enough.

"""

from math import asin, pi, sqrt


def xn(n):
    return (n + 1 - sqrt(2 * n)) / (n * n + 1)


def area(n):
    x = xn(n)
    return ((1 - x) * sqrt(1 - (1 - x) ** 2) + asin(1 - x) - n * x * x + 2 * x - pi / 2) / (2 - pi / 2)


def p587():
    n = 1
    while area(n) > 0.001:
        n += 1
    return n
