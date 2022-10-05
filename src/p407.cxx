#include "common.h"
#include "mathfuncs.h"

#include <algorithm>
#include <array>
#include <memory>
#include <vector>

#include <cmath>

/*

Given an integer and its prime factorization, n = p1^a1 * p2^a2 * ... * pk^ak,
the Chinese Remainder Theorem defines a ring isomorphism,

    Z_n = Z_{p1^a1} + Z_{p2^a2} + ... + Z_{pk^ak}

The only idempotents in Z_{p^a} for any prime p are 0 and 1. Therefore, Z_n has
2^k idempotents corresponding to every possible selection of 0 or 1 in each
Z_{pi^ai}.

ANSWER 39782849136421

*/

/* Computes sieve where nth entry is
 * - if n is composite: smallest prime factor of n.
 * - if n is prime: 0.
 */
std::unique_ptr<short[]> smallest_prime_factor(int N)
{
    // create sieve
    auto sieve = std::make_unique<short[]>(N);
    for (short i = 2; i * i < N; i++) {
        if (sieve[i] == 0) {
            for (int j = i * i; j < N; j += i) {
                if (sieve[j] == 0) {
                    sieve[j] = i;
                }
            }
        }
    }
    return sieve;
}

/* Calculate prime factorization, with speed up from `smallest_prime_factors`. */
std::vector<mf::PrimePower> prime_factorize(int x, short* sieve)
{
    std::vector<mf::PrimePower> facts;
    short p;
    int a;
    while (sieve[x] >= 2) {
        p = sieve[x];
        a = 0;
        while (sieve[x] == p or x == p) {
            x /= p;
            a++;
        }
        if (a != 0) {
            facts.push_back({p, a});
        }
    }
    if (x > 1 && sieve[x] == 0) {
        facts.push_back({x, 1});
    }
    return facts;
}

int max_idem(int* arr, int size, int N, int i = 0, int running_sum = 0)
{
    /* Recursively find largest idempotent. */

    if (i == size) {
        return running_sum % N;
    }

    return std::max(max_idem(arr, size, N, i + 1, running_sum), max_idem(arr, size, N, i + 1, running_sum + arr[i]));
}

long p407()
{
    const int size = 10'000'000;
    long sum_idem = 0;

    auto sieve = smallest_prime_factor(size + 1);

    for (int n = 2; n <= size; n++) {
        // prime factorize
        std::vector<mf::PrimePower> factors = prime_factorize(n, sieve.get());

        // find base idempotents
        int num_idems = factors.size();
        int m, b, a;
        auto idems = std::make_unique<int[]>(num_idems);
        for (int i = 0; i < num_idems; i++) {
            m = pow(factors[i].base, factors[i].exp);
            b = n / m;
            a = mf::modular_inverse(b, m) * b % n;
            idems[i] = a;
        }
        // find largest idempotent
        sum_idem += max_idem(idems.get(), num_idems, n);
    }

    return sum_idem;
}

int main()
{
    TIMED(printf("%ld\n", p407()));
}
