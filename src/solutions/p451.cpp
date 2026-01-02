#include "mf/mathfuncs.hpp"

/*

The strategy is similar to that of Problem 407. Given an integer and its prime
factorization, n = p1^a1 * p2^a2 * ... * pk^ak, the Chinese Remainder Theorem
defines a ring isomorphism,

    Z_n = Z_{p1^a1} * Z_{p2^a2} * ... * Z_{pk^ak}

When p != 2, the ring Z_{p^a} is cyclic and has two elements which square to 1:
1 and -1, but one is just the negative of the other. However, the rings Z_8,
Z_16, Z_32, ... are not cyclic and there are 4 square roots of 1 in
each of these rings, two of which are negatives of the others.

    1, 2^{k-1} - 1, 2^{k-1} + 1, -1

So, the goal is to find all "base square roots of 1" corresponding to
the choices

    (-1, 1, 1, ...), (1, -1, 1, ...), (1, 1, -1, ...) ...

If Z_n contains a special case Z_8, Z_16, Z_32, ... then we also need to add
an extra "base square root of 1" corresponding to the choice

    (2^{k-1} + 1, 1, 1, ...)

We find the combination of these base roots to find the largest product mod n,
that is not n-1. See this link for more info:
https://en.wikipedia.org/wiki/Primitive_root_modulo_n.

(Related problems: 271, 407)

ANSWER 153651073760956

*/

/**
 * Copied from Problem 407.
 *
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

/* Recursively find largest root. */
long find_max_root(const std::vector<long>& base_roots, int num_roots, int n, int i = 0, long running_prod = 1)
{
    if (i == num_roots) {
        return running_prod < n - 1 ? running_prod : 1;
    }

    return std::max(
        find_max_root(base_roots, num_roots, n, i + 1, running_prod),
        find_max_root(base_roots, num_roots, n, i + 1, (running_prod * base_roots[i]) % n));
}

long p451()
{
    constexpr int limit = 20'000'000;

    const auto sieve = mf::prime_factor_sieve(limit + 1);

    long sum = 0;
    for (long n = 3; n <= limit; n++) {
        // get prime factorization
        const auto factors = mf::prime_factorize(n, sieve);

        // Z_8, Z_16, Z_32, ... are not cyclic groups under multiplication but
        // decompose into a product of cyclic groups: Z_2 * Z_{2^{k-2}}
        const bool non_cyclic = (factors[0].base == 2 && factors[0].exp >= 3);

        // find all base roots
        const int num_roots = factors.size() + (non_cyclic ? 1 : 0);
        std::vector<long> base_roots(num_roots);

        int i = 0;
        for (const auto& factor : factors) {
            // first, find the multiplicative unit, like (1, 0, 0, ...)
            const long unit = get_base_idempotent(n, factor);

            // find the non-cyclic base root, like (1 + 2^{k-1}, 1, 1, ...)
            if (non_cyclic && factor.base == 2) {
                const long root = 1 + static_cast<long>(pow(2, factor.exp - 1)) * unit;
                base_roots[i] = ((root % n) + n) % n;
                i++;
            }

            // find the base root, like (-1, 1, 1, ...)
            const long root = 1 - 2 * unit;
            base_roots[i] = ((root % n) + n) % n;
            i++;
        }

        // find largest root
        sum += find_max_root(base_roots, num_roots, n);
    }

    return sum;
}

int main()
{
    printf("%ld\n", p451());
}
