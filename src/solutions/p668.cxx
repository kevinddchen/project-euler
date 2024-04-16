#include "common.h"
#include "mathfuncs.h"

#include <vector>

/*

ANSWER

*/

bool is_smooth(long n)
{
    const std::vector<mf::PrimePower> facts = mf::prime_factorize(n);
    for (const auto& fact : facts) {
        if (fact.base * fact.base >= n) {
            return false;
        }
    }
    return true;
}

long p0()
{
    constexpr long limit = 10'000'000'000;

    // {
    //     long count = 1;
    //     for (long n = 2; n <= limit; ++n) {
    //         if (is_smooth(n)) {
    //             // printf("%ld\n", n);
    //             ++count;
    //         }
    //     }

    //     printf("count=%ld\n", count);
    // }

    printf("===\n");
    // ------------------------------------------------------------------------

    const long sqrt_limit = sqrt(limit);

    // generate primes up to sqrt(limit)
    const std::vector<bool> sieve = mf::prime_sieve(sqrt_limit + 1);
    std::vector<long> primes;
    for (int i = 2; i < sieve.size(); ++i) {
        if (sieve[i]) {
            primes.push_back(i);
        }
    }

    // keeps track of all numbers encountered
    std::vector<long> nums = {1};

    // keeps track of count of smooth numbers
    long count = 1;

    for (long p : primes) {
        std::vector<long> new_nums;

        for (long num : nums) {
            while (num * p <= limit) {
                new_nums.push_back(num);
                if (p < num) {
                    // printf("%ld\n", num * p);
                    ++count;
                }
                num *= p;
            }
        }

        nums = new_nums;
    }
    printf("count=%ld\n", count);
    return 0;
}

int main()
{
    printf("%ld\n", p0());
}
