#include "mf/mathfuncs.hpp"

#include <algorithm>

/*

We note that if N has prime factorization p1^k1 * p2^k2 * ... * pn^kn, then the total roundness can be computed by:

      (k1 + 1) * (k2 + 1) * ... * (kn + 1) - 1
    + (k1 // 2 + 1) * (k2 // 2 + 1) * ... * (kn // 2 + 1) - 1
    + ...
    + (k1 // kmax + 1) * (k2 // kmax + 1) * ... * (kn // kmax + 1) - 1

The first term in the sum represents the number of divisors of N, excluding 1. The second term in the sum represents the
number of divisors of N that are squares, exclusing 1. And so forth.

ANSWER 40410219

*/

constexpr long MOD = 1'000'000'007;

/**
 * Computes the total roundness of n!.
 */
long total_roundness_factorial(int n)
{
    // first, compute prime factor sieve: nth element is the smallest factor of n
    const std::vector<int> sieve = mf::prime_factor_sieve(n + 1);

    // second, compute prime factorization of n!
    std::vector<int> prime_powers(n + 1, 0);  // pth element is power of p in prime factorization of n!

    for (int i = 2; i <= n; ++i) {
        // iterate over 1, 2, ..., n and combine prime factorizations
        int x = i;
        while (x != 1) {
            const int p = sieve[x];
            assert(p != 0);
            ++prime_powers[p];
            x /= p;
        }
    }

    // collate and sort powers in decreasing order. the sorting allows us to make an optimization
    std::vector<int> powers;
    for (int p = 2; p <= n; ++p) {
        if (prime_powers[p] > 0) {
            powers.push_back(prime_powers[p]);
        }
    }
    std::sort(powers.begin(), powers.end(), std::greater<int>());

    // third, compute total roundness
    long total = 0;
    for (int level = 1; level <= powers[0]; ++level) {
        long prod = 1;
        for (auto k : powers) {
            // break if remaining parts of the product are all 1s. this is an important optimization
            if (k < level) {
                break;
            }
            prod = (prod * (k / level + 1)) % MOD;
        }
        total = (total + prod - 1) % MOD;
    }

    return total;
}

long p926()
{
    return total_roundness_factorial(10'000'000);
}

int main()
{
    printf("%ld\n", p926());
}
