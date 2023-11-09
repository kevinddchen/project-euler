#include "common.h"
#include "mathfuncs.h"

#include <algorithm>
#include <array>
#include <memory>
#include <vector>

#include <cmath>

/*

Given an integer and its prime factorization, n = p1^a1 * p2^a2 * ... * pk^ak,
the Chinese Remainder Theorem defines a ring isomorphism,

    Z_n = Z_{p1^a1} * Z_{p2^a2} * ... * Z_{pk^ak}

The only multiplicative idempotents in Z_{p^a} for any prime p are 0 and 1:
m * m = m (mod p^a) implies m(m-1) = d * p^a for some integer d. If d is
nonzero, then p^a must divide m or m-1, which is not possible since m < p^a.
Thus d=0 and m=0 or =1.

Therefore, Z_n has 2^k multiplicative idempotents corresponding to all possible
choices of picking 0 or 1 for each Z_{pi^ai}. We first compute the k "base
idempotents" corresponding to the choices,

    (1, 0, 0, ...), (0, 1, 0, ...), (0, 0, 1, ...), ...

Then we find the combination of these base idempotents with the largest sum
modulo n.

(Related problems: 271, 451)

ANSWER 39782849136421

*/

/**
 * In the ring Z_n, for a given prime factor p^a find the integer 1 <= m < n
 * such that m = 1 (mod p^a) and m = 0 (mod q^b) for all other prime factors
 * q^b of n.
 */
long get_base_idempotent(long n, const mf::PrimePower& factor)
{
    const long x = mf::pow(factor.base, factor.exp);  // pi^ai
    const long n_x = n / x;
    // find b * n_x (mod n) such that b * n_x = 1 (mod x)
    return (mf::modular_inverse(n_x, x) * n_x) % n;
}

/**
 * Recursively find largest idempotent.
 */
long max_idem(long* base_idems, int num_idems, int n, int i = 0, int running_sum = 0)
{
    if (i == num_idems) {
        return running_sum % n;
    }

    return std::max(
        max_idem(base_idems, num_idems, n, i + 1, running_sum),
        max_idem(base_idems, num_idems, n, i + 1, running_sum + base_idems[i]));
}

long p407()
{
    constexpr int size = 10'000'000;

    const auto sieve = mf::prime_factor_sieve(size + 1);

    long sum_idem = 0;
    for (int n = 2; n <= size; n++) {
        // prime factorize
        const auto factors = mf::prime_factorize(n, sieve.get());

        // find base idempotents
        const int num_idems = factors.size();
        const auto base_idems = std::make_unique<long[]>(num_idems);
        for (int i = 0; i < num_idems; i++) {
            base_idems[i] = get_base_idempotent(n, factors[i]);
        }

        // find combination giving largest idempotent
        sum_idem += max_idem(base_idems.get(), num_idems, n);
    }

    return sum_idem;
}

int main()
{
    TIMED(printf("%ld\n", p407()));
}
