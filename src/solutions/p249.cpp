#include "mf/mathfuncs.hpp"

/*

Similar to Problem 250: keep an array `counts` whose ith element represents the
number of subsets whose sum equals i. Start with all elements equal zero,
except `counts[0] = 1` for the empty set. For each k = 2, 3, ..., 4999, update
the array according to the rule:

    new_counts[i] = counts[i] + counts[i - k]

The answer is `counts` summed at all prime indices. All that remains is to
figure out the length for `counts`, which should be able to store the sum of
all primes 2, 3, ..., 4999. It turns out that `counts` should have length ~1.5
million, which is not too bad.

ANSWER 9275262564250418

*/

long p249()
{
    constexpr int limit = 5000;
    constexpr long mod = 1e16;

    // get primes up to `limit`
    std::vector<int> primes;
    {
        const auto sieve = mf::prime_sieve(limit);
        for (int p = 2; p < limit; ++p) {
            if (sieve[p]) {
                primes.push_back(p);
            }
        }
    }

    int sum_primes = 0;
    for (auto prime : primes) {
        sum_primes += prime;
    }

    // create an array tracking counts (up to the sum of all primes)
    std::vector<long> counts(sum_primes + 1, 0);
    counts[0] = 1;

    for (auto prime : primes) {
        // perform counts[i] <- counts[i] + counts[i - p]. this can be done
        // in-place if we iterate over i in descending order.
        for (int i = sum_primes; i >= prime; --i) {
            counts[i] = (counts[i] + counts[i - prime]) % mod;
        }
    }

    // add up `counts` at prime indices
    long sum_counts = 0;
    const auto sieve = mf::prime_sieve(sum_primes + 1);
    for (int p = 2; p <= sum_primes; ++p) {
        if (sieve[p]) {
            sum_counts = (sum_counts + counts[p]) % mod;
        }
    }

    return sum_counts;
}

int main()
{
    printf("%ld\n", p249());
}
