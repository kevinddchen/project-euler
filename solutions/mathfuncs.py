#!/usr/bin/python

def isPrime(x):
    """Returns True if x is prime. """
    if x < 2:       return False
    if x == 2:      return True
    if x%2 == 0:    return False
    for y in xrange(3, int(x**0.5)+1, 2):
        if x%y == 0: return False
    return True

def primeSieve(limit, pass_to_mutable=[None]):
    """Prime sieve, as generator. Option to pass sieve by reference. """
    a = [True]*(limit+1)
    pass_to_mutable[0] = a
    a[0] = a[1] = False
    for i, isprime in enumerate(a):
        if isprime:
            yield i
            for n in xrange(i*i, limit+1, i):
                a[n] = False

def primeFactorize(x):
    """Generates unique prime factors and multiplicities. """
    assert x != 0
    i = 0
    while x%2 == 0:
        i += 1
        x //= 2
    if i != 0: yield 2, i
    y = 3
    while y*y <= x:
        i = 0
        while x%y == 0:
            i += 1
            x //= y
        if i != 0: yield y, i
        y += 2
    if x != 1: yield x, 1

def choose(n, k):
    """Returns n choose k. """
    p = 1
    for i in xrange(1, k+1):
        p = p*(n+1-i)/i
    return p

def gcd(a, b):
    """Returns greatest common divisor of a and b. """
    while b != 0:
        a, b = b, a%b
    return a

def extended_gcd(a, b):
    """Returns Bezout coefficients and gcd. """
    s, old_s = 0, 1
    t, old_t = 1, 0
    r, old_r = b, a
    while r != 0:
        q = old_r // r
        old_r, r = r, old_r - q*r
        old_s, s = s, old_s - q*s
        old_t, t = t, old_t - q*t
    return (old_s, old_t, old_r)

def modularInverse(a, n):
    """Returns the multiplicative inverse of a mod n. """
    s, t, r = extended_gcd(a, n)
    if r > 1: return 0
    return s%n

## for prime factorization sieve: Problem 69
## for divisors: Problem 44
## for permutations: Problem Problem 76

