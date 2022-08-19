# ANSWER 55

from .mathfuncs import PrimeSieve


def circular(n, sieve):
    """Returns True if n is a circular prime."""
    n = str(n)
    for i in range(len(n)):
        if not sieve[int(n[i:] + n[:i])]:
            return False
    return True


def p35():
    ps = PrimeSieve(1000000)
    for _ in ps:
        pass

    return sum(1 for p, isprime in enumerate(ps.sieve) if isprime and circular(p, ps.sieve))
