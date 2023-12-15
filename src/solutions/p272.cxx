#include "common.h"
#include "mathfuncs.h"

/*

From Problem 271, we know that if we decompose n into its prime factors,

    n = p1^a1 * p2^a2 * ... * pk^ak

then the number of cube roots of unity (mod n) is equal to the product of the
number of cube roots of unity for each prime factor. For a prime factor p, it
has 3 cube roots of unity if p-1 is divisible by 3, and 1 cube root of unity
otherwise. One exception is p = 3^k for k >= 2, which has 3 cube roots of
unity.

Since 243 = 3^5, we want to generate all n whose prime factorization contains
exactly 5 elements from the list {7, 9, 13, 19, 31, 37, ...}.

This can be done by generating primes and then filtering them by whether they
are in this list (i.e. whether they have 3 cube roots of unity) or not. Then
iterate over all combinations of 5 primes from this list, and consider all
numbers formed by taking products of these 5 primes to some power. Then for
each of these numbers, we further consider all products with the other primes
not in the list. This sounds like a lot of nested loops, but with enough
filtering it can run in a reasonable time.

ANSWER 8495585919506151122

*/

long p272()
{
    // we are looking for n where n <= limit and C(n) = 243
    const long limit = 100'000'000'000;

    // smallest n such that C(n) = 243
    const long smallest_solution = 7 * 9 * 13 * 19 * 31;

    // only need to generate primes up to this limit
    const int prime_limit = limit / (7 * 9 * 13 * 19);
    const auto prime_sieve = mf::prime_sieve(prime_limit + 1);

    // split primes into "candidates" (i.e. have three cube roots of unity) and
    // "trivials" (i.e. only cube root of unity is 1).
    std::vector<long> cands = {9};  // special case is 3^k for k >= 2
    std::vector<long> trivs = {2};
    for (int p = 5; p <= prime_limit; p += 2) {
        if (prime_sieve[p]) {
            if (p % 3 == 1) {
                cands.push_back(p);
            } else {
                trivs.push_back(p);
            }
        }
    }

    // generate all n built out of trivials, where C(n) = 1
    std::vector<long> triv_prods = {1, 3};  // 3 is special case

    const long triv_prod_limit = limit / smallest_solution;
    for (const long triv : trivs) {
        const long size = triv_prods.size();  // vector is modified in the loop
        for (int i = 0; i < size; i++) {
            long prod = triv_prods[i] * triv;
            while (prod <= triv_prod_limit) {
                triv_prods.push_back(prod);
                prod *= triv;
            }
        }
    }

    // sort for later binary search
    std::sort(triv_prods.begin(), triv_prods.end());

    // compute partial sums
    std::vector<long> triv_prods_partial_sums(triv_prods.size() + 1);
    triv_prods_partial_sums[0] = 0;
    for (int i = 0; i < triv_prods.size(); i++) {
        triv_prods_partial_sums[i + 1] = triv_prods_partial_sums[i] + triv_prods[i];
    }

    // iterate over 5-combinations of candidates, and iterate over all products
    // of those candidates, not exceeding `limit`. the nested loops are ugly,
    // but it gets the job done.
    long total = 0;

    for (int i = 0; i < cands.size() - 4; i++) {
        if (cands[i] * cands[i + 1] * cands[i + 2] * cands[i + 3] * cands[i + 4] > limit) {
            break;
        }
        for (int j = i + 1; j < cands.size() - 3; j++) {
            if (cands[i] * cands[j] * cands[j + 1] * cands[j + 2] * cands[j + 3] > limit) {
                break;
            }
            for (int k = j + 1; k < cands.size() - 2; k++) {
                if (cands[i] * cands[j] * cands[k] * cands[k + 1] * cands[k + 2] > limit) {
                    break;
                }
                for (int s = k + 1; s < cands.size() - 1; s++) {
                    if (cands[i] * cands[j] * cands[k] * cands[s] * cands[s + 1] > limit) {
                        break;
                    }
                    for (int t = s + 1; t < cands.size(); t++) {
                        if (cands[i] * cands[j] * cands[k] * cands[s] * cands[t] > limit) {
                            break;
                        }
                        // iterate over products of p^n that are less than `limit`

                        std::vector<long> cand_prods = {cands[i] * cands[j] * cands[k] * cands[s] * cands[t]};

                        for (long cand : {cands[i], cands[j], cands[k], cands[s], cands[t]}) {
                            // note (special case): candidate can be 9, and this will generate powers involving 9, 81,
                            // 729, ... The other powers 27, 243, ... are generated by multiplying by the 3 in
                            // `triv_prods`.
                            const int size = cand_prods.size();  // vector is modified in the loop
                            for (int i = 0; i < size; i++) {
                                long prod = cand_prods[i] * cand;
                                while (prod <= limit) {
                                    cand_prods.push_back(prod);
                                    prod *= cand;
                                }
                            }
                        }

                        // for each product, find the number of trivial products that can be multiplied together without
                        // exceeding `limit`. This is done by binary search through the sorted `triv_prods`.
                        for (const long prod : cand_prods) {
                            const long max_trivial = limit / prod;
                            const auto iter = std::upper_bound(triv_prods.begin(), triv_prods.end(), max_trivial);
                            const long slice = iter - triv_prods.begin();
                            total += triv_prods_partial_sums[slice] * prod;
                        }
                    }
                }
            }
        }
    }

    return total;
}

int main()
{
    printf("%ld\n", p272());
}
