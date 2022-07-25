# ANSWER 402

from math import factorial
from time import time

# saved values
fact = [factorial(x) for x in range(10)]

chain_dict = {}


def chain(x, prev=[]):
    x = int("".join(sorted(str(x), reverse=True)))
    if x in chain_dict:
        return chain_dict[x], 0
    if x in prev:
        chain_dict[x] = len(prev) - prev.index(x)
        return chain_dict[x], -chain_dict[x]

    prev.append(x)
    s = sum(fact[int(c)] for c in str(x))
    length, offset = chain(s, prev)
    offset += 1
    chain_dict[x] = length + max(0, offset)
    return length, offset


def p74():
    return sum(1 for x in range(1, 1000000) if sum(chain(x)) == 60)


if __name__ == "__main__":
    time_start = time()
    print(p74())
    print("Time: {0:.3f}".format(time() - time_start))
