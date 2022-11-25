# ANSWER 55

from mathfuncs import PrimeSieve


def circular(n, sieve):
    """Returns True if n is a circular prime."""
    n = str(n)
    for i in range(len(n)):
        if not sieve[int(n[i:] + n[:i])]:
            return False
    return True


def p35():
    sieve = PrimeSieve(1000000).sieve
    return sum(1 for p, isprime in enumerate(sieve) if isprime and circular(p, sieve))
