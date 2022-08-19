# ANSWER 648

from math import factorial


def p20():
    return sum(int(n) for n in str(factorial(100)))
