#include <mf/mathfuncs.hpp>

#include <array>

/*

This is a straight-forward dynamic programming problem. Keep an array `counts`
whose ith element represents the number of subsets whose sum equals i mod 250.
Start with all elements equal zero, except `counts[0] = 1` for the empty set.
For each k = 1^1, 2^2, ..., 250250^250250, update the array according to the
rule:

    new_counts[i] = counts[i] + counts[(i - k^k) mod 250]

The answer is `counts[0] - 1` (minus 1 for the empty set).

As a fun fact, this is a variation of the more famous problem of finding the
number of subsets of the array {1, 2, 3, ...}. There, the answer can be
computed by hand. There is a great Youtube video on this:
https://youtu.be/bOXCLR3Wric

ANSWER 1425480602091519

*/


long p250()
{
    const long mod = 1e16;

    // keeps track of the number of subsets with this sum, mod 250
    std::array<long, 250> counts;
    counts.fill(0);
    counts[0] = 1;

    for (long k = 1; k <= 250250; ++k) {
        // compute k^k mod 250
        long pow = mf::modular_power(k % 250, k, 250);

        // copy the counts
        std::array<long, 250> new_counts = counts;

        for (long sum = 0; sum < 250; ++sum) {
            // add `pow` to the subset sum, mod 250
            const int new_sum = (sum + pow) % 250;
            new_counts[new_sum] = (new_counts[new_sum] + counts[sum]) % mod;
        }

        counts = new_counts;
    }

    // return the number of subsets with sum = 0 mod 250, minus 1 for the empty set
    return counts[0] - 1;
}

int main()
{
    printf("%ld\n", p250());
}
