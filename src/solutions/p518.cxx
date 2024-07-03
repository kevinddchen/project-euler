#include "common.h"
#include "containers.h"
#include "mathfuncs.h"

#include <unordered_map>
#include <unordered_set>
#include <vector>

/*

ANSWER

*/

long p0()
{
    const long limit = 100;

    // find all primes < limit
    std::vector<long> primes;
    {
        const auto sieve = mf::prime_sieve(limit);
        primes.push_back(2);
        for (long p = 3; p < limit; p += 2) {
            if (sieve[p]) {
                primes.push_back(p);
            }
        }
    }

    // for all pairs of primes, compute ratio. put into a map
    // (p_j + 1) / (p_i + 1) --> { p_i, p_j }
    std::unordered_multimap<mf::Frac, std::pair<long, long>> ratio_to_pair;
    std::unordered_set<mf::Frac> ratios;
    {
        const size_t num_primes = primes.size();
        for (int i = 0; i < num_primes; ++i) {
            for (int j = i + 1; j < num_primes; ++j) {
                const mf::Frac frac(primes[j] + 1, primes[i] + 1);
                ratio_to_pair.emplace(std::make_pair(frac, std::make_pair(primes[i], primes[j])));
                ratios.insert(frac);
            }
        }
    }


    // for (auto ratio : ratios){
    //     printf("%d/%d\n", ratio.numer, ratio.denom);
    //     auto range = ratio_to_pair.equal_range(ratio);
    //     for (auto it = range.first; it != range.second; ++it) {
    //         printf("    (%d, %d)\n", it->second.first, it->second.second);
    //     }

    // }

    return 0;
}

int main()
{
    printf("%ld\n", p0());
}
