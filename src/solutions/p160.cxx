#include "common.h"
#include "mathfuncs.h"

/*

A trailing zero is produced for each factor of 10 in the factorial. So the
strategy is to compute the factorial, but omit all factors of 5. For each
factor of 5 we omit, we also have to divide by a factor of 2. The naive
approach is too slow, so we have to be a bit more clever.

Let f(n) be the factorial of n but omitting all multiples of 5, i.e.

    f(4) = 24, f(5) = 24, f(6) = 144, ...

We can note that the answer we are trying to compute is equal to

    f(1,000,000,000,000) * f(1,000,000,000,000 / 5) * f(1,000,000,000,000 / 25) * ...

so the question becomes how to compute f(n) efficiently. Luckily, if we are
working modulo 100,000, then the elements of the product in f(n) is periodic.
For instance,

    f(1,000,000,000,000) = f(100,000) ^ (1,000,000,000,000 / 100,000) mod 100,000

But remember we have to also divide out a factor of 2 for each power of 5 we
have omitted in computing the factorials. This can be done modulo 100,000 by
exploiting the fact that the powers of 2 are periodic modulo 100,000 (2 is not
invertible so 1 is not in this periodic cycle).

ANSWER 16576

*/

/**
 * Computes the period of `x` modulo `m`, i.e. the smallest `k > 0` such that
 * `x^a = x^(a+k) mod m` for some `a`.
 */
int get_period(long x, long m)
{
    std::vector<int> seen(m, 0);

    long power = 1;
    for (int i = 1;; ++i) {
        power = (power * x) % m;
        assert(power != 0);  // there is no period if x^a = 0 mod m
        if (seen[power] > 0) {
            return i - seen[power];
        }
        seen[power] = i;
    }
}

long p160()
{
    const long N = 1'000'000'000'000;
    const long mod = 100'000;

    const int period = get_period(2, mod);

    // Populate a table of f(n) modulo `mod` up to `mod`
    std::vector<long> f(mod + 1);
    f[0] = 1;
    for (long i = 1; i <= mod; ++i) {
        if (i % 5 == 0) {
            f[i] = f[i - 1];
        } else {
            f[i] = (f[i - 1] * i) % mod;
        }
    }

    // Compute the product as described in the description above. Alont the
    // way, we will also count the number of powers of 5 we omitted.
    long result = 1;
    long powers_of_five = 0;

    long x = N;
    while (x > 0) {
        const long quotient = x / mod;
        result = (result * mf::modular_power(f[mod], quotient, mod)) % mod;

        const long remainder = x % mod;
        result = (result * f[remainder]) % mod;

        x /= 5;
        powers_of_five += x;
    }

    // For each power of 5 we omitted, we need to divide by 2. Instead, we can
    // multiply by an appropriate power of 2.

    const long num_mults = (period - powers_of_five % period);
    result = (result * mf::modular_power(2, num_mults, mod)) % mod;

    return result;
}

int main()
{
    printf("%ld\n", p160());
}
