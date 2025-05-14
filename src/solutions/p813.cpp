#include <mf/mathfuncs.hpp>

#include <set>

/*

Let X denote the xor product, and ^ denote the xor power.

We first note an observation:
    11^1 = 11       = 2^3 + 2^1 + 2^0
    11^2 = 69       = 2^6 + 2^2 + 2^0
    11^4 = 4113     = 2^12 + 2^4 + 2^0
    11^8 = 16777473 = 2^24 + 2^8 + 2^0
or in general,
    11^(2**k) = 2**(3 * 2**k) + 2**(2**k) + 1
Note that `+` on unique powers of 2 is the same as the xor operation. Then, since
    8**12 * 12**8 = 2**52 + 2**57 + 2**59 + 2**60 + 2**63 + 2**64
we have
    P(8**12 * 12**8)
    = (11 ^ 2**52) X (11 ^ 2**57) X ... X (11 ^ 2**64)
    = (2**(3 * 2**52) + 2*(2**52) + 1) X (2**(3 * 2**57) + 2**(2**57) + 1) X ... X (2**(3 * 2**64) + 2**(2**64) + 1)
The xor product distributes over the `+`, which are just xor operations. This
gives us a sum over powers of 2, which can be computed.

For tractability, we define y = 2**(2**52). The expansion then simplifies to
    = (y**3 + y + 1) X (y**(3 * 32) + y**32 + 1) X ... X (y**(3 * 2**12) + y**(2**12) + 1)
y mod 1,000,000,007 can be computed using Fermat's little theorem.

ANSWER 14063639

*/

/**
 * Expand the xor product in `unexpanded_powers_of_y`, throwing away powers of
 * y that are encountered an even number of times (due to the xor operation).
 */
void recurse(
    const std::vector<std::vector<int>>& unexpanded_powers_of_y,
    std::set<int>& powers_of_y,
    int depth = 0,
    int partial_sum = 0)
{
    if (depth == unexpanded_powers_of_y.size()) {
        // reached base case
        if (const auto it = powers_of_y.find(partial_sum); it == powers_of_y.end()) {
            // sum is not in set, add it
            powers_of_y.insert(partial_sum);
        } else {
            // sum is in set, remove it
            powers_of_y.erase(it);
        }
        return;
    }

    const auto& powers = unexpanded_powers_of_y[depth];
    for (const int power : powers) {
        recurse(unexpanded_powers_of_y, powers_of_y, depth + 1, partial_sum + power);
    }
}

long p813()
{
    const long m = 1'000'000'007;

    // first, find the (y^(3k) + y^k + 1) terms involved in the xor product.
    // this vector only contains the powers of y.
    std::vector<std::vector<int>> unexpanded_powers_of_y;
    {
        int a = 6561;  // 3^8
        int power = 1;
        while (a > 0) {
            if (a & 1) {
                unexpanded_powers_of_y.push_back({3 * power, power, 0});
            }
            a >>= 1;
            power <<= 1;
        }
    }

    // next, expand the terms of the xor product
    std::set<int> powers_of_y;
    recurse(unexpanded_powers_of_y, powers_of_y);

    // compute y = 2^(2^52) mod m using Fermat's little theorem
    long y_mod_m;
    {
        const long p = mf::modular_power(2, 52, m - 1);
        y_mod_m = mf::modular_power(2, p, m);
    }

    // finally, add all the powers of y
    long result = 0;
    long y_to_the_i = 1;
    int max_i = *powers_of_y.rbegin();

    for (int i = 0; i <= max_i; i++) {
        if (powers_of_y.find(i) != powers_of_y.end()) {
            result = (result + y_to_the_i) % m;
        }
        y_to_the_i = (y_to_the_i * y_mod_m) % m;
    }

    return result;
}

int main()
{
    printf("%ld\n", p813());
}
