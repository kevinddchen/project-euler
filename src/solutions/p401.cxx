#include "common.h"

/*

The answer is the sum of k^2 * floor(n/k) for k = 1, 2, ..., n where n = 10^15.
For large k, floor(n/k) is the same value for many values of k, so its actually
faster to find ranges of k where floor(n/k) = target, and then use the sum of
consecutive squares formula. If we take this alternative stragegy for values
of k > sqrt(n), then we can compute the sum in O(sqrt(n)) time.

ANSWER 281632621

*/

/**
 * Return sum of squares of i = 1, 2, ..., n. Equals n(n+1)(2n+1)/6. Care has
 * to be taken to avoid integer overflow.
 */
long sum_consecutive_squares(long n, long mod)
{
    long a = n;
    long b = n + 1;
    long c = 2 * n + 1;

    if (n % 2 == 0) {
        a /= 2;
    } else {
        b /= 2;
    }

    const long n_mod_3 = n % 3;
    if (n_mod_3 == 0) {
        a /= 3;
    } else if (n_mod_3 == 1) {
        c /= 3;
    } else {
        b /= 3;
    }

    a %= mod;
    b %= mod;
    c %= mod;
    return (((a * b) % mod) * c) % mod;
}

/**
 * If floor(n/k) = t, then k in (n/(t+1), n/t]. Returns the lowest and highest
 * integers k in this interval.
 */
void get_bounds(long n, long target, long& lower, long& upper)
{
    lower = n / (target + 1) + 1;
    upper = n / target;
}

long p401()
{
    const long limit = 1'000'000'000'000'000;
    const long mod = 1'000'000'000;

    const long sqrt_limit = sqrt(limit);  // approx 3.2 * 10^7

    long sum = 0;

    // compute sum for large values of k by finding floor(n/k) = target
    long lower, upper;
    for (long target = 1; target < sqrt_limit; target++) {
        get_bounds(limit, target, lower, upper);
        const long sum_squares = sum_consecutive_squares(upper, mod) - sum_consecutive_squares(lower - 1, mod);
        sum = (sum + (target * sum_squares) % mod) % mod;
    }

    // compute sum for small values of k directly
    for (long k = 1; k < lower; k++) {
        const long k_squared = (k * k) % mod;
        const long multiples = (limit / k) % mod;
        const long add = (k_squared * multiples) % mod;
        sum = (sum + add) % mod;
    }

    sum = (sum + mod) % mod;  // get positive remainder
    return sum;
}

int main()
{
    TIMED(printf("%ld\n", p401()));
}
