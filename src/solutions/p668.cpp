#include "mf/mathfuncs.hpp"

#include <vector>

/*

Starting with the set {1}, we generate all numbers <= 10^10 by iterating over
prime numbers in increasing order and multiplying against members of the set.
For instance, considering 2 gives us all powers of 2,

    {1, 2, 4, 8, 16, ...}

And then considering 3, we generate all numbers that are formed by a product
of 2 or 3,

    {1, 2, 3, 4, 6, 8, 9, ...}

Note that in this process, if we are multiplying a prime p with a member of the
set n, the product p*n is square root smooth iff p<n. This is because all
factors of n are <=p, so the largest prime factor of p*n is p, but p^2 < p*n.

The time complexity of the algorithm described above is pretty bad, so we have
to do some pruning to get below the 1 minute mark. One important optimization
is that since we are iterating over primes in increasing order, we can drop
elements of the set if their product with the prime exceeds the 10^10 limit.

ANSWER 2811077773

*/

long p668()
{
    constexpr long limit = 10'000'000'000;

    // generate primes up to sqrt(limit)
    const std::vector<bool> sieve = mf::prime_sieve(sqrt(limit) + 1);
    std::vector<long> primes;
    for (int i = 2; i < static_cast<int>(sieve.size()); ++i) {
        if (sieve[i]) {
            primes.push_back(i);
        }
    }

    // keeps track of elements in the set
    std::vector<long> nums = {1};

    // keeps track of count of smooth numbers
    long count = 1;

    for (long p : primes) {
        std::vector<long> new_nums;

        for (long num : nums) {
            while (num * p <= limit) {
                new_nums.push_back(num);
                if (p < num) {
                    ++count;
                }
                num *= p;
            }
        }

        nums = new_nums;
    }

    return count;
}

int main()
{
    printf("%ld\n", p668());
}
