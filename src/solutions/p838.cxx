#include "common.h"
#include "mathfuncs.h"

#include <unordered_map>
#include <unordered_set>

/*

This turns out to be the "Set cover problem", which is NP-hard.

The approach I took was using logic to determine which prime factors had to be
in f(N). This was done in a couple of steps:

1.  First, find the prime factorizations of 3, 13, 23, 33, ... Any primes in
    this list must be in f(N). Otherwise, if the prime factorization does not
    contain primes ending in 3, the set of distinct prime factors for that
    number is added to `factor_sets`.

2.  If a set in `factor_sets` contains only one element, that element must be
    in f(N).

3.  We define a "singleton" to be a prime factor that only appears in one set
    in `factor_sets` and that set only contains two prime factors. Thus, if we
    have a prime factor p that is associated with s_i singletons, then p must
    be in f(N) if log(p) < sum_i(log(s_i)). This is because if p is not in
    f(N), then to satisfy all the singletons we must add all s_i to f(N), which
    would give a larger number.

After these 3 steps, we have reduced the size of `factor_sets` from 23048 to
569. This is not small enough, so we generalized the notion of a "singleton" to
prime factors that only appear in 2 (and later on, only 3) other sets. This
allowed us to determine that the following primes must be in f(N):

547, 557, 607, 617, 727, 757, 709, 719, 739, 829, 839, 859

This could be programed, but it would take a while, so I was lazy and just
hardcoded it. This reduced the size of `factor_sets` to 44, which is small
enough to be brute forced.

Not one of my favorite solutions...

ANSWER 250591.442792

*/

/**
 * Remove all sets in `factor_sets` that contain `p`.
 */
void filter_out_prime(std::vector<std::vector<int>>& factor_sets, int p)
{
    std::vector<std::vector<int>> new_factor_sets;
    for (const auto& set : factor_sets) {
        if (std::find(set.begin(), set.end(), p) == set.end()) {
            new_factor_sets.push_back(set);
        }
    }
    factor_sets = new_factor_sets;
}

/**
 * Remove duplicate sets in `factor_sets`.
 */
void remove_duplicates(std::vector<std::vector<int>>& factor_sets)
{
    // this can be done by looking at the product, since all are sets of primes
    std::unordered_set<int> products;
    std::vector<std::vector<int>> new_factor_sets;
    for (const auto& set : factor_sets) {
        long prod = 1;
        for (int p : set) {
            prod *= p;
        }
        if (products.find(prod) == products.end()) {
            products.insert(prod);
            new_factor_sets.push_back(set);
        }
    }
    factor_sets = new_factor_sets;
}

double p838()
{
    const int limit = 1'000'000;

    std::vector<int> primes;                    // prime factors of the integer we are computing
    std::vector<std::vector<int>> factor_sets;  // unique prime factors for each unaccounted integer

    // step 1: initial population of these two lists
    {
        // compute prime factorization of 3, 13, 23, 33, ...
        const std::unique_ptr<int[]> sieve = mf::prime_factor_sieve(limit + 1);
        for (int i = 3; i <= limit; i += 10) {
            const std::vector<mf::PrimePower> facts = mf::prime_factorize(i, sieve.get());

            // if prime, add to `primes`
            if (facts.size() == 1 && facts[0].exp == 1) {
                assert(facts[0].base == i);
                primes.push_back(i);
                continue;
            }

            // otherwise, add to `factor_sets` if no prime factor ends in 3
            std::vector<int> set;
            for (const auto& fact : facts) {
                if (fact.base % 10 == 3) {
                    break;
                }
                set.push_back(fact.base);
            }
            if (set.size() == facts.size()) {  // no primes end in 3
                factor_sets.push_back(set);
            }
        }
    }

    // this is necessary for some of our counting later on
    remove_duplicates(factor_sets);

    // step 2: if a factor set contains one element, it should be added to `primes`
    {
        std::unordered_set<int> new_primes;
        for (const auto& set : factor_sets) {
            if (set.size() == 1) {
                new_primes.insert(set[0]);
            }
        }

        for (int p : new_primes) {
            primes.push_back(p);
            filter_out_prime(factor_sets, p);
        }
    }

    // hard-coded primes; see comment at top of file
    for (int p : {547, 557, 607, 617, 727, 757, 709, 719, 739, 829, 839, 859}) {
        primes.push_back(p);
        filter_out_prime(factor_sets, p);
    }

    // step 3: filter using singletons
    {
        // keep looping until nothing changes
        size_t prev_primes_size = -1;
        while (primes.size() != prev_primes_size) {
            prev_primes_size = primes.size();

            // find singletons
            std::unordered_map<int, int> counts;
            for (const auto& set : factor_sets) {
                for (int p : set) {
                    counts[p]++;
                }
            }

            // if log(number) is less than the sum of log(s) over its singletons, then it should be added to `prime`
            std::unordered_map<int, float> scores;
            for (const auto& set : factor_sets) {
                if (set.size() != 2) {
                    continue;
                }
                if (counts[set[0]] == 1) {
                    scores[set[1]] += std::log(set[0]);
                } else if (counts[set[1]] == 1) {
                    scores[set[0]] += std::log(set[1]);
                }
            }

            for (const auto& [p, score] : scores) {
                if (std::log(p) < score) {
                    primes.push_back(p);
                    filter_out_prime(factor_sets, p);
                }
            }
        }
    }

    // brute force the solution
    {
        std::unordered_set<int> flattened_factor_sets;
        for (const auto& set : factor_sets) {
            for (int p : set) {
                flattened_factor_sets.insert(p);
            }
        }

        std::vector<int> all_factors;
        for (int p : flattened_factor_sets) {
            all_factors.push_back(p);
        }

        int size = all_factors.size();
        assert(size < 20);  // can't be too big

        double best_score = -1;
        std::unordered_set<int> best_factors;
        for (long i = 1; i < mf::pow(2, size); i++) {
            std::unordered_set<int> subset;

            double score = 0;
            for (int j = 0; j < size; j++) {
                if (i & (1 << j)) {
                    subset.insert(all_factors[j]);
                    score += std::log(all_factors[j]);
                }
            }

            if (best_score > 0 && score > best_score) {
                continue;
            }

            // check all sets are satified
            bool success = true;
            for (const auto& set : factor_sets) {
                bool found = false;
                for (int p : set) {
                    if (subset.find(p) != subset.end()) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    success = false;
                    break;
                }
            }
            if (success) {
                best_score = score;
                best_factors = subset;
            }
        }

        for (int p : best_factors) {
            primes.push_back(p);
        }
    }

    // done, compute the answer
    double total = 0;
    for (int p : primes) {
        total += std::log(p);
    }

    return total;
}

int main()
{
    TIMED(printf("%.6f\n", mf::round(p838(), 6)));
}
