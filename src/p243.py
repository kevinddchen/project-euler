# ANSWER: 892371480

"""

The resilience of d is phi(d)/(d-1), where phi(d) is the totient function.
This is minimized by taking the product of many consecutive primes. Therefore
we generate primordials (i.e. products of consecutive primes, 2*3*5*7* ...)
until the resilience reaches below 15499/947444. Then we take the previous
primordial, and the answer should be a multiple of it.

"""

from time import time

from mathfuncs import is_prime


def prime_gen():
    yield 2
    y = 3
    while True:
        if is_prime(y):
            yield y
        y += 2


def p243():
    G = prime_gen()

    # get primordial just below ratio
    d, tot = 1, 1
    p = next(G)
    while tot * (p - 1) * 94744 >= (d * p - 1) * 15499:
        d *= p
        tot *= p - 1
        p = next(G)

    # find smallest d, which is a multiple of the primordial found above
    n = 1
    while tot * n * 94744 >= (d * n - 1) * 15499:
        n += 1
    return n * d


if __name__ == "__main__":
    time_start = time()
    print(p243())
    print("Time: {0:.3f}".format(time() - time_start))
