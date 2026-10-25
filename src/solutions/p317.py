"""

Can be solved by hand. See PDF for explanation.

"""

from math import pi

ANSWER = 1856532.8455


def p317():
    volume = 2 * pi * (20 * 20 / (2 * 9.81)) * (100 + 20 * 20 / (2 * 9.81)) ** 2
    return round(volume, 4)
