#include "mf/mathfuncs.hpp"

/*

If n = 10*a + b, then f(n) = a + m*b. We note, working in mod p, that n and f(n) are both zero/nonzero when m is the
modular inverse of 10.

ANSWER 1601912348822

*/

long p274()
{
    constexpr long limit = 1e7;

    // generate primes
    const auto sieve = mf::prime_sieve(limit);

    long sum_m = 0;

    // special case: p=3
    sum_m += mf::modular_inverse(10, 3);

    // iterate over remaining p coprime to 10
    for (long p = 7; p < limit; p += 2) {
        if (!sieve[p])  // if not prime
            continue;

        sum_m += mf::modular_inverse(10, p);
    }

    return sum_m;
}

int main()
{
    printf("%ld\n", p274());
}
