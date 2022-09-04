# ANSWER 34029210557338

from .mathfuncs import prime_factorize


def add_dict(d, x, i):
    if x in d:
        d[x] += i
    else:
        d[x] = i


def p203():
    S = set([1])
    for n in range(2, 50):
        prod = 1
        facts = {}
        for k in range(1, n // 2 + 1):
            prod = prod * (n + 1 - k) // k
            for pf in prime_factorize(n + 1 - k):
                add_dict(facts, pf.base, pf.exp)
            if k > 1:
                for pf in prime_factorize(k):
                    add_dict(facts, pf.base, -pf.exp)
            squarefree = True
            for x in facts:
                if facts[x] > 1:
                    squarefree = False
                    break
            if squarefree:
                S.add(prod)
    return sum(S)
