#include <mf/mathfuncs.hpp>

#include <algorithm>
#include <numeric>
#include <vector>

/*

It can be shown by induction that if a_n is a triangle number, then a_{n+k} equals a_n + kth triangle number (at least
until we encounter another triangle number). This implies that if a_n is a triangle number in the sequence, in order to
find the next triangle number in the sequence, we need to find the smallest triangle number to add to a_n such that the
sum is also a triangle number.

Mathematically, we want to find the smallest positive integer k where

    n (n + 1) / 2 + k (k + 1) / 2 = m (m + 1) / 2

We can re-arrange this into

    n (n + 1) = (m - k) (m + k - 1) := a * b

Thus, we let `a` iterate through the divisors of n (n + 1), and the product with
the smallest positive integer k = (b - a - 1) / 2 gives us the next triangle number.
Note that we need `a < n` in order to have a positive k.

In term of the implementation, we have to be very careful to avoid integer overflow, as in order to reach the 70th
triangle number we will quickly hit values that exceed the max value of a C++ long.

ANSWER 6795261671274

*/

/**
 * Given prime factorization, produce divisors less than `n`.
 */
std::vector<long> divisors_less_than_n(const std::vector<mf::PrimePower>& prime_factors, long n)
{
    std::vector<long> divisors = {1};
    for (const auto& prime_factor : prime_factors) {
        // first, generate all prime powers
        std::vector<long> powers;
        powers.reserve(prime_factor.exp);
        long power = 1;
        for (int i = 0; i < prime_factor.exp; ++i) {
            power *= prime_factor.base;
            if (power >= n) {
                break;
            }
            powers.push_back(power);
        }
        // multiply prime powers against all divisors
        std::vector<long> new_divisors;
        new_divisors.reserve(powers.size() * divisors.size());
        for (auto divisor : divisors) {
            for (auto power : powers) {
                const long new_divisor = power * divisor;
                if (new_divisor >= n) {
                    break;
                }
                new_divisors.push_back(new_divisor);
            }
        }
        divisors.insert(divisors.end(), new_divisors.begin(), new_divisors.end());
    }
    return divisors;
}

/**
 * Given triangle number n * (n + 1), return tuple (k, m) where k is the smallest postive integer such that
 * n * (n + 1) + k * (k + 1) is also a triangle number, m * (m + 1).
 */
std::pair<long, long> compute_next_n(long n)
{
    // prime factorize n * (n + 1)
    const auto n_pf = mf::prime_factorize(n);
    const auto np1_pf = mf::prime_factorize(n + 1);
    const auto pf = mf::merge_prime_factors(n_pf, np1_pf);

    // get divisors of n * (n + 1) less than n, in decreasing order
    auto divisors = divisors_less_than_n(pf, n);
    std::sort(divisors.begin(), divisors.end(), std::greater<long>());

    // since a are decreasing, the first valid k we encounter will be the smallest
    for (long a : divisors) {
        // compute b = n * (n + 1) / a, taking care to avoid overflow
        const long d1 = std::gcd(n, a);
        const long d2 = std::gcd(n + 1, a);
        assert(a == d1 * d2);
        const long b = (n / d1) * ((n + 1) / d2);

        const long twice_k = b - a - 1;
        if (twice_k % 2 == 1) {
            continue;
        }

        const long k = twice_k / 2;
        const long m = k + a;
        return std::make_pair(k, m);
    }
    throw std::runtime_error("Could not find next n");
}


long p955()
{
    constexpr long TARGET_COUNT = 70;

    long idx = 0;
    long n = 2;  // a = 3

    for (int i = 2; i <= TARGET_COUNT; ++i) {
        const auto [k, next_n] = compute_next_n(n);
        idx += k;
        n = next_n;
    }

    return idx;
}

int main()
{
    printf("%ld\n", p955());
}
