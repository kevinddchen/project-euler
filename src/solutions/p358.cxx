#include "common.h"
#include "mathfuncs.h"

/*

We note that any cyclic number can be identified with the first p-1 decimal
places of the fraction 1/p, for some prime number p. The leftmost digits of the
cyclic number correspond to the most significant digits of the fraction, so we
know that p must be a prime number between

    1 / 0.00000000138 ~= 724637681 and
    1 / 0.00000000137 ~= 729927007

Moreover, since we know that the cyclic number ends with 56789, using the fact
that the cyclic number * p equals to 10^{p-1} - 1 = 999....999, we can further
constrain p by requiring that the product with 56789 is a number that ends with
99999.

These two conditions yields 3 candidates for p: 725509891, 726509891, and
729809891. We can explicitly check each p that the fractions 1/p gives a cyclic
number, and it turns out that p = 729809891 is the unique solution.

ANSWER 3284144505

*/

/**
 * Since the cyclic number * p = 999...999, if the cyclic number ends with
 * 56789 then multiplied with p we should get a number that ends with 99999.
 */
bool correct_rightmost(long p)
{
    const long mod = 100000;
    return mf::modular_product(56789, p % mod, mod) == 99999;
}

constexpr long UNSET_QUOTIENT = -1;

/**
 * Explicitly check if 1/p gives a cyclic number. If yes, returns true and the
 * num of the digits of the cyclic number. Otherwise, returns false.
 */
std::pair<bool, long> sum_cyclic_digits(long p)
{
    long sum = 0;
    long quotient = UNSET_QUOTIENT;
    long remainder = 1;
    for (int i = 1; i < p; ++i) {
        // check if not cyclic
        if (remainder == 1 && quotient != UNSET_QUOTIENT) {
            return std::make_pair(false, 0);
        }
        const long dividend = remainder * 10;
        const auto dv = std::div(dividend, p);
        quotient = dv.quot;
        remainder = dv.rem;

        sum += quotient;
    }
    return std::make_pair(true, sum);
}

long p358()
{
    const long MIN = 1 / 0.00000000138;
    const long MAX = 1 / 0.00000000137;

    for (long p = MIN; p <= MAX; ++p) {
        if (correct_rightmost(p) && mf::is_prime(p)) {
            const auto [is_cyclic, sum_digits] = sum_cyclic_digits(p);
            if (is_cyclic) {
                return sum_digits;
            }
        }
    }

    throw std::runtime_error("No cyclic number found");
}

int main()
{
    printf("%ld\n", p358());
}
