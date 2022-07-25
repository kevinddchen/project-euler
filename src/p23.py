# ANSWER 4179871

from time import time

from .p21 import sum_proper_divisors


def p23():
    N = 28123
    abundants = []
    for x in range(1, N + 1):
        if sum_proper_divisors(x) > x:
            abundants.append(x)
    summable = set()
    for i, a in enumerate(abundants):
        for b in abundants[i:]:
            if a + b <= N:
                summable.add(a + b)
            else:
                break
    # sum of all numbers under 28124 minus sum of abundants
    return N * (N + 1) // 2 - sum(summable)


if __name__ == "__main__":
    time_start = time()
    print(p23())
    print("Time: {0:.3f}".format(time() - time_start))
