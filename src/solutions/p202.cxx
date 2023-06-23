#include "common.h"
#include "mathfuncs.h"

/*

This problem is very similar to p351, since we can unfold the reflections to
form a triangular wedge. A laser beam path then corresponds to a pair of
integers (a, b) where gcd(a, b) = 1. The taxicab distance a+b = n is related to
the number of bounces B by n = (B+3)/2. All what remains is check that the point
(a, b) corresponds to vertex C, which is true when a == b (mod 3).

In summary, the answer to this problem is equivalent to "for n, how many a < n
are coprime and a+n = 0 (mod 3)?" Since n is so big in this problem, we need an
efficient way to count the coprime a's (rather than naively using gcd, which is
slow). We do the counting here by inclusion-exclusion. For instance, the
integers coprime to 3*5*7 excludes all multiples of 3 and 5, but we need to add
back multiples of 15 since they were counted twice.

ANSWER 1209002624

*/

/* Count multiples of a that satisfy k*a < n and k*a + n = 0 (mod 3). */
long count_multiples(long a, long n)
{
    long k_max = (n - 1) / a;
    if (a % 3 == 0 && n % 3 == 0) {
        return k_max;
    }
    if (a % 3 == 0 && n % 3 != 0) {
        return 0;
    }
    int m = (k_max * a + n) % 3;
    if (m != 0) {
        k_max -= a % 3 == m ? 1 : 2;
    }
    // k_max is the largest valid value for k.
    return (k_max - 1) / 3 + 1;
}

long p202()
{
    const long bounces = 12017639147;
    const long n = (bounces + 3) / 2;

    const auto prime_factors = mf::prime_factorize(n);

    // old_factors[0] keeps track of odd-length products of distinct prime factors.
    // old_factors[1] "            " even-length "                               ".
    std::array<std::vector<long>, 2> old_factors, new_factors;
    old_factors[0] = {};
    old_factors[1] = {1};
    for (const auto& pp : prime_factors) {
        new_factors[0] = {};
        new_factors[1] = {};
        for (auto odd_o_f : old_factors[0]) {
            new_factors[1].push_back(odd_o_f * pp.base);
        }
        for (auto even_o_f : old_factors[1]) {
            new_factors[0].push_back(even_o_f * pp.base);
        }
        old_factors[0].insert(old_factors[0].end(), new_factors[0].begin(), new_factors[0].end());
        old_factors[1].insert(old_factors[1].end(), new_factors[1].begin(), new_factors[1].end());
    }

    long count = 0;
    for (auto even : old_factors[1]) {
        count += count_multiples(even, n);  // count_multiples(1, n) includes all integers.
    }
    for (auto odd : old_factors[0]) {
        count -= count_multiples(odd, n);  // exclude all multiples of a prime factor.
    }

    return count;
}

int main()
{
    TIMED(printf("%ld\n", p202()));
}
