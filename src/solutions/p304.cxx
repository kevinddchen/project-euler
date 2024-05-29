#include "common.h"
#include "mathfuncs.h"

#include <array>
#include <vector>

/*

The key is to quickly generate 100,000 primes larger than 10^14. It turns out
that this can be accomplished with a sieve and the primes less than 10^7, since
the next prime after 10^7 is q = 10,000,019 and there are 11,787,044 primes
between 10^14 and q^2.

To compute the nth fibonacci number modulo m, we use the closed-form matrix
representation,

    {{1, 1}, {1, 0}}^n = {{F_(n-1), F_n}, {F_n, F_(n-1)}}

and then efficiently compute the modular power of the matrix in a way analogous
to how it is done for integers.

ANSWER 283988410192

*/

using Matrix2l = std::array<std::array<long, 2>, 2>;

/**
 * Modular matrix multiplication.
 */
Matrix2l mod_mul(const Matrix2l& a, const Matrix2l& b, long m)
{
    Matrix2l result;
    result[0][0] = (mf::modular_product(a[0][0], b[0][0], m) + mf::modular_product(a[0][1], b[1][0], m)) % m;
    result[0][1] = (mf::modular_product(a[0][0], b[0][1], m) + mf::modular_product(a[0][1], b[1][1], m)) % m;
    result[1][0] = (mf::modular_product(a[1][0], b[0][0], m) + mf::modular_product(a[1][1], b[1][0], m)) % m;
    result[1][1] = (mf::modular_product(a[1][0], b[0][1], m) + mf::modular_product(a[1][1], b[1][1], m)) % m;
    return result;
}

/**
 * Compute the nth fibonacci number, mod m.
 */
long fib_mod(long n, long m)
{
    // Uses the fact that {{1, 1}, {1, 0}}^n = {{F_(n-1), F_n}, {F_n, F_(n-1)}}
    // Then use an analogous exponentiation by squaring algorithm
    Matrix2l base;
    base[0] = {1, 1};
    base[1] = {1, 0};
    Matrix2l result;
    result[0] = {1, 0};
    result[1] = {0, 1};

    while (n > 0) {
        if (n & 1) {  // if (n % 2) == 1
            result = mod_mul(result, base, m);
        }
        base = mod_mul(base, base, m);
        n >>= 1;
    }

    return result[0][1];
}


/**
 * Generate the smallest prime greater than n.
 */
long next_prime(long n)
{
    n += 1 + n % 2;  // next odd number greater than n
    while (!mf::is_prime(n)) {
        n += 2;
    }
    return n;
}

long p304()
{
    const long mod = 1234567891011;

    const long limit = 100'000;

    const long N = 1e14;
    const long sqrt_N = sqrt(N);

    // generate primes up to 10^7
    std::vector<long> primes = {2};
    {
        const auto sieve = mf::prime_sieve(sqrt_N);
        for (long p = 3; p < sieve.size(); p += 2) {
            if (sieve[p]) {
                primes.push_back(p);
            }
        }
    }

    // q = prime after 10^7
    const long q = next_prime(sqrt_N);

    // do prime sieve on integers 1e14 to q * q
    // hopefully, there are more than 100,000 primes in this range
    const long size = q * q - N;
    std::vector<bool> sieve(size);
    {
        // initialize sieve
        for (int i = 0; i < size; ++i) {
            sieve[i] = true;
        }

        for (auto p : primes) {
            // N % p gives the remainder, so p less this gives the first multiple of p greater than N
            // we take a final modulo to get the first multiple greater _or equal_ than N
            for (long j = (p - N % p) % p; j < size; j += p) {
                sieve[j] = false;
            }
        }
    }

    // sum `fib_mod` on first 100,000 primes
    long sum = 0;
    {
        long count = 0;
        for (int i = 0; i < size; ++i) {
            if (!sieve[i]) {
                continue;
            }

            sum = (sum + fib_mod(N + i, mod)) % mod;
            ++count;

            if (count == limit) {
                break;
            }
        }
        assert(count == limit);
    }

    return sum;
}

int main()
{
    printf("%ld\n", p304());
}
