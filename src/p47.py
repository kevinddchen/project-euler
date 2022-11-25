# ANSWER 134043

from mathfuncs import prime_factorize


def p47():
    L = [len([pf.base for pf in prime_factorize(x)]) for x in [2, 3, 4, 5]]
    j = 2
    while L != [4, 4, 4, 4]:
        L.pop(0)
        L.append(len([pf.base for pf in prime_factorize(j + 4)]))
        j += 1
    return j
