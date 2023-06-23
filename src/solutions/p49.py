# ANSWER 296962999629

"""

It is faster to generate 4-digit primes, go through permutations for a larger
prime, then find the next term in the arithmetic sequence and check that it is
a prime and permutation.

"""

from itertools import permutations

from mathfuncs import prime_sieve


def is_permutation(a, b):
    return set(str(a)) == set(str(b))


def p49():
    sieve = prime_sieve(10000)

    for p, isprime in enumerate(sieve):
        # search for 4 digit primes
        if p < 1000 or not isprime:
            continue
        # cycle through permutations for prime
        for perm in permutations(str(p)):
            q = int("".join(perm))
            if q > p and 10000 > q and sieve[q]:
                # get next prime in sequence, check is permutation
                r = q + (q - p)
                if 10000 > r and sieve[r] and is_permutation(r, p):
                    # not first one
                    if p != 1487:
                        return str(p) + str(q) + str(r)
