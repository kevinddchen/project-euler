#include "mf/mathfuncs.hpp"

/*

By playing around, you can convince yourself that for all m, n > 1:

    S(n, n) = 8n - 11
    S(m, n) = 6(m - n) + 8n - 13 , m > n
    S(m, n) = S(n, m)

Now we want to find solutions where S(m, n) = p^2. First off, we can rule out
solutions for p=2 by checking this case by hand, so we can assume without loss
of generality that p is odd. Since p^2 = 1 (mod 8) for all odd primes p, we
note that cannot have S(n, n) = p^2. Thus, for each prime 2 < p < 1,000,000, we
try to find all solutions to

    p^2 + 13 = 6a + 8n

where n > 1 and a > 0. Because p is odd, we can actually divide both sides by 2.

ANSWER 2057774861813004

*/

/**
 * Count how many ways x = 3a + 4n for n > 1 and a > 0.
 */
long count_ways(long x)
{
    assert(x >= 8);

    // first value of n
    long first_n;
    long mod = (x - 8) % 3;
    if (mod == 0) {
        first_n = 2;
    } else if (mod == 1) {
        first_n = 3;
    } else {
        first_n = 4;
    }

    // upper limit for n
    const long max_n = (x - 1) / 4;  // -1 so if x multiple of 4, we have a > 0

    if (max_n < first_n) {
        return 0;
    }
    return (max_n - first_n) / 3 + 1;
}

long p313()
{
    const long limit = 1e6;

    const auto sieve = mf::prime_sieve(limit);

    long count = 0;
    // skip 2, since no solutions
    for (long p = 3; p < limit; p += 2) {
        if (sieve[p]) {
            count += 2 * count_ways((p * p + 13) / 2);
        }
    }

    return count;
}

int main()
{
    printf("%ld\n", p313());
}
