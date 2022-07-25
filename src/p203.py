# ANSWER 34029210557338

from time import time

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
            for f, i in prime_factorize(n + 1 - k):
                add_dict(facts, f, i)
            if k > 1:
                for f, i in prime_factorize(k):
                    add_dict(facts, f, -i)
            squarefree = True
            for x in facts:
                if facts[x] > 1:
                    squarefree = False
                    break
            if squarefree:
                S.add(prod)
    return sum(S)


if __name__ == "__main__":
    time_start = time()
    print(p203())
    print("Time: {0:.3f}".format(time() - time_start))
