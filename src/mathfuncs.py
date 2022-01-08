#!/usr/bin/python

import math

def is_prime(x):
    '''Returns True if x is prime. Runs in O(sqrt(x)) time. '''
    assert x > 1 and x == int(x), "x must be integer greater than 1."
    if x == 2:      return True
    if x%2 == 0:    return False
    y = 3
    while y*y <= x:
        if x%y == 0: return False
        y += 2
    return True


def prime_sieve(N, sieve=[]):
    '''Efficiently generates all primes up to N. Pass an empty list to `sieve`
    to access the sieve directly. '''
    sieve.extend(True for _ in range(N))
    sieve[0] = sieve[1] = False
    for n, isprime in enumerate(sieve):
        if isprime:
            for y in range(n*n, N, n): # sieve out all multiples
                sieve[y] = False
            yield n


def prime_factorize(x):
    '''Find prime factorization of x = p_1^(a_1) * p_2^(a_2) * ... * p_k^(a_k).
    Returns tuples (p_i, a_i) for each prime p_i in ascending order. Runs in
    O(sqrt(x)) time. '''

    def divide_out(x, p):
        '''Divide out p from x as many times as possible.'''
        i = 0
        while x%p == 0:
            i += 1
            x //= p
        return x, i

    assert x > 1 and x == int(x), "x must be integer greater than 1."
    x, i = divide_out(x, 2) # divide out multiples of 2
    if i != 0:
        yield 2, i
    y = 3
    while y*y <= x:
        x, i = divide_out(x, y) # divide out multiples of 2
        if i != 0: 
            yield y, i
        y += 2
    if x != 1: 
        yield x, 1 # remainder of x is prime


# def extended_gcd(a, b):
#     '''Returns a tuple (s, t, r) containing the Bezout coefficients and gcd,
#     i.e. a*s + b*t = r. '''
#     s, old_s = 0, 1
#     t, old_t = 1, 0
#     r, old_r = b, a
#     while r != 0:
#         q = old_r // r
#         old_r, r = r, old_r - q*r
#         old_s, s = s, old_s - q*s
#         old_t, t = t, old_t - q*t
#     return (old_s, old_t, old_r)

## sum of proper divisors: p21
## iterate through divisors: p44
## totient sieve: p69
## integer partition: p76 
## totient: p188
## binary search: p187
