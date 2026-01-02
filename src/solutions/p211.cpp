#include "mf/mathfuncs.hpp"

#include <vector>

/*

The sum of squares of the divisors of n can be computed efficiently by first
computing the prime factorization of n. If

    n = p_1^{a_1} * p_2^{a_2} * ... * p_k^{a_k}

Then the sum of squares of the divisors of n is

    (1 + p_1^2 + p_1^4 + ... + p_1^{2a_1}) *
    (1 + p_2^2 + p_2^4 + ... + p_2^{2a_2}) *
    ...
    (1 + p_k^2 + p_k^4 + ... + p_k^{2a_k})

The prime factorizations of all numbers up to 64,000,000 can be computed
efficiently using a sieve.

ANSWER 1922364685

*/

/**
 * Compute sum of the squares of the divisors of n.
 */
long sum_of_divisors_square(long n, const std::vector<int>& sieve)
{
    long result = 1;
    for (const mf::PrimePower& factor : mf::prime_factorize(n, sieve)) {
        // first, compute 1 + p^2 + p^4 + ... + p^{2a}
        // this is done via loop instead of geometric sum formula to prevent overflow
        long power_of_fact_sq = 1;  // tracks 1, p^2, p^4, ..., p^{2a}
        long sum = 1;               // tracks the sum of the above
        for (long i = 0; i < factor.exp; ++i) {
            power_of_fact_sq *= factor.base * factor.base;
            sum += power_of_fact_sq;
        }
        result *= sum;
    }
    return result;
}

bool is_square(long n)
{
    const long root = std::sqrt(n);
    return root * root == n;
}

long p211()
{
    const long limit = 64'000'000;

    // sieve of prime factors
    const std::vector<int> sieve = mf::prime_factor_sieve(limit);

    long sum = 1;  // for n=1
    for (long n = 2; n < limit; ++n) {
        const long div_sq_sum = sum_of_divisors_square(n, sieve);
        if (is_square(div_sq_sum)) {
            sum += n;
        }
    }

    return sum;
}

int main()
{
    printf("%ld\n", p211());
}
