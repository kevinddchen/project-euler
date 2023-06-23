# ANSWER 55

from mathfuncs import prime_sieve


def circular(n, sieve):
    """Returns True if n is a circular prime."""
    n = str(n)
    for i in range(len(n)):
        if not sieve[int(n[i:] + n[:i])]:
            return False
    return True


def p35():
    sieve = prime_sieve(1000000)
    return sum(1 for p, isprime in enumerate(sieve) if isprime and circular(p, sieve))
