#include "mf/mathfuncs.hpp"

/*

The sum over terms with g(n) = 1 equals the number of square-free integers up
to N = 10^14. If this function is denoted Q(n), note that it can be calculated
using the Mobius function mu(n):

    Q(n) = sum_{d=1}^{sqrt(n)} mu(d) * floor(n / d^2)

Next, note that the sum over terms with g(n) = 4 equals 4 * Q(floor(N / 4)).
The Q(n) function to find square-free multiples of 4, or otherwise the number
will be divisible by a larger square number. In general, the sum over terms
with g(n) = k*k equals k * k * Q(floor(N / (k * k))).

ANSWER 94586478

*/


/**
 * Calculates the Mobius function for all integers up to `size` using a sieve.
 */
std::vector<int8_t> mobius_sieve(int size)
{
    const auto primes = mf::prime_sieve(size);

    // initialize sieve
    std::vector<int8_t> sieve(size);
    for (int i = 1; i < size; i++) {
        sieve[i] = 1;
    }

    // sieve
    for (int i = 2; i < size; i++) {
        if (!primes[i]) {
            continue;
        }

        // for each multiple of i, multiply by -1
        // for each multiple of i^2, multiply by 0
        for (int j = 1; i * j < size; j++) {
            if (j % i == 0) {
                sieve[i * j] = 0;
            } else {
                sieve[i * j] *= -1;
            }
        }
    }
    return sieve;
}

/**
 * Count the number of square-free integers up to and including `n`.
 * @param n
 * @param mobius The Mobius function for all integers up to `sqrt(n)`.
 */
long count_square_free(long n, const std::vector<int8_t>& mobius)
{
    long sum = 0;
    for (long d = 1; d * d <= n; d++) {
        sum += mobius[d] * (n / (d * d));
    }
    return sum;
}

long p745()
{
    const long limit = 100'000'000'000'000;
    const long mod = 1'000'000'007;

    const long sqrt_limit = floor(sqrt(limit));
    const auto mobius = mobius_sieve(sqrt_limit + 1);

    long sum = 0;
    for (long i = 1; i <= sqrt_limit; i++) {
        sum = (sum + i * i * count_square_free(limit / (i * i), mobius)) % mod;
    }

    return sum;
}

int main()
{
    printf("%ld\n", p745());
}
