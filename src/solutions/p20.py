from math import factorial

ANSWER = 648


def p20():
    return sum(int(n) for n in str(factorial(100)))
