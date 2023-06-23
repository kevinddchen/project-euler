# ANSWER -59231

"""

We can optimize slightly: n=0 implies b must be positive and prime. n=1 implies
a >= 1-b

"""

from mathfuncs import is_prime, prime_sieve


def quadratic_chain(a, b):
    """Returns maximum n where n^2 + a*n + b returns prime numbers."""
    n = 0
    while n * n + a * n + b > 1 and is_prime(n * n + a * n + b):
        n += 1
    return n


def p27():
    # (length of chain, product)
    maxim = (0, 0)

    # b must be positive and prime.
    for b, is_prime_ in enumerate(prime_sieve(1000)):
        if not is_prime_:
            continue
        # a >= 1-b
        for a in range(1 - b, 1000):
            test = (quadratic_chain(a, b), a * b)
            if test > maxim:
                maxim = test
    return maxim[1]
