# ANSWER 2944730

from mathfuncs import prime_sieve


def recurse(primes, limit, prod=1, i=0):
    C = 1
    for j in range(i, len(primes)):
        if prod * primes[j] > limit:
            break
        C += recurse(primes, limit, prod * primes[j], j)
    return C


def p204():
    primes = [p for p, is_prime in enumerate(prime_sieve(100)) if is_prime]
    return recurse(primes, 10**9)
