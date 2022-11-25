# ANSWER 612407567715

from itertools import combinations, product

from mathfuncs import is_prime


def matchPattern(pattern, d, DIGITS):
    number = [d] * DIGITS
    for prod in product(range(10), repeat=len(pattern)):
        for i, place in enumerate(pattern):
            number[place] = prod[i]
        if number[-1] == 0:
            continue
        x = sum(y * 10**i for i, y in enumerate(number))
        if is_prime(x):
            yield x


def p111():
    DIGITS = 10
    S = 0
    for d in range(10):
        for M in range(DIGITS - 1, 0, -1):
            prime_list = []
            for pattern in combinations(range(DIGITS), DIGITS - M):
                prime_list.extend(matchPattern(pattern, d, DIGITS))
            if len(prime_list) != 0:
                break
        S += sum(prime_list)
    return S
