# ANSWER 538319652

"""

We use the fact that

    B(n) = B(n-1) * n^n / n!

So we recursively keep track of the prime factorization of B(n), which can
compute the sum of divisors efficiently. routine.

"""

from mathfuncs import prime_factorize, prime_sieve


def p650():
    N = 20_000
    M = 1_000_000_007
    S = 1

    primes = [p for p, is_prime in enumerate(prime_sieve(N)) if is_prime]
    n_primes = len(primes)

    # store look-up table of indices for each prime
    prime_i = {}
    for i, p in enumerate(primes):
        prime_i[p] = i

    # inverse of p-1 mod M
    inverses = [pow(p - 1, -1, M) for p in primes]

    # curr_f keeps track of prime factorization of B(n)
    # sub_f keeps track of prime factorization of n!
    curr_f = [0 for _ in range(n_primes)]
    sub_f = [0 for _ in range(n_primes)]

    for n in range(2, N + 1):
        for pf in prime_factorize(n):
            p_i = prime_i[pf.base]
            curr_f[p_i] += pf.exp * n
            sub_f[p_i] += pf.exp

        for i in range(n_primes):
            curr_f[i] -= sub_f[i]

        d_sum = 1
        for p_i, a in enumerate(curr_f):
            p = primes[p_i]
            if a != 0:
                d_sum *= pow(p, int(a + 1), M) - 1
                d_sum = (d_sum * inverses[p_i]) % M

        S = (S + d_sum) % M

    return S
