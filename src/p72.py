# ANSWER 303963552391

"""

The number of reduced fractions with denominator d is precisely the totatives of
d. Therefore the answer is the sum of phi(n) for n = 2 to 10^6, where phi is the
totient function.

"""

from time import time

from p69 import totient_sieve


def p72():
    return sum(tot for _, tot in totient_sieve(1_000_001))


if __name__ == "__main__":
    time_start = time()
    print(p72())
    print("Time: {0:.3f}".format(time() - time_start))
