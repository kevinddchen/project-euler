# ANSWER 18613426663617118

"""

Let p, q be consecutive primes and k be the number of digits in p. Then we are
looking for a that satisfies a*10^k + p = 0 mod q. As q is prime we can find a
explicitly, a = -p*10^(-k) mod q.

"""

from mathfuncs import prime_sieve


def p134():
    total = 0
    LIMIT = 1000000

    p = 0
    for q, is_prime in enumerate(prime_sieve(LIMIT + 100)):  # small buffer
        if not is_prime:
            continue
        if p > LIMIT:
            break
        if q > 5:
            k = len(str(p))  # num of digits in p
            a = (q - p) * pow(10, -1, q) ** k % q
            total += a * 10**k + p
        p = q
    return total
