#include "common.h"
#include "mathfuncs.h"

#include <unordered_map>

/*

For a given s, we are counting the number of n such that 1 < n < N that solve
the following system of congruences:

    n = 1 (mod 2)
    n = 1 (mod 3)
    n = 1 (mod 4)
    ...
    n != 1 (mod s + 1)

This can be solved by the Chinese Remainder Theorem, where we are essentially
just solving for n = 1 (mod M) where M is the LCM of the first couple
consecutive integers 2, 3, 4, ...

ANSWER 1617243

*/

/**
 * Count the number of n such that 1 < n < N and n = 1 (mod m).
 */
long count(long N, long m)
{
    return (N - 2) / m;
}

long P(long s, long N)
{
    // find LCM of 2, 3, 4, ..., s by computing prime factorizations
    std::unordered_map<long, int> facts;
    for (long i = 2; i <= s; i++) {
        const auto new_facts = mf::prime_factorize(i);
        for (const auto& fact : new_facts) {
            if (facts.find(fact.base) == facts.end()) {
                facts[fact.base] = fact.exp;
            } else if (facts[fact.base] < fact.exp) {
                facts[fact.base] = fact.exp;
            }
        }
    }
    long prev_prod = 1;
    for (const auto& [base, exp] : facts) {
        prev_prod *= mf::pow(base, exp);
    }

    // find LCM with s+1 added to set
    long curr_prod = prev_prod;
    {
        const auto new_facts = mf::prime_factorize(s + 1);
        for (const auto& fact : new_facts) {
            if (facts.find(fact.base) == facts.end()) {
                curr_prod *= mf::pow(fact.base, fact.exp);
            } else if (facts[fact.base] < fact.exp) {
                curr_prod *= mf::pow(fact.base, fact.exp - facts[fact.base]);
            }
        }
    }

    const long prev_count = count(N, prev_prod);
    const long curr_count = count(N, curr_prod);
    return prev_count - curr_count;
}

long p601()
{
    long sum = 0;
    long power_of_4 = 1;
    for (int i = 1; i <= 31; i++) {
        power_of_4 *= 4;
        sum += P(i, power_of_4);
    }
    return sum;
}

int main()
{
    TIMED(printf("%ld\n", p601()));
}
