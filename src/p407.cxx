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

/* Recursively find largest idempotent. */
int max_idem(int* arr, int size, int N, int i = 0, int running_sum = 0)
{
    if (i == size) {
        return running_sum % N;
    }

    return std::max(max_idem(arr, size, N, i + 1, running_sum), max_idem(arr, size, N, i + 1, running_sum + arr[i]));
}

long p407()
{
    constexpr int size = 10'000'000;
    long sum_idem = 0;

    const auto sieve = mf::prime_factor_sieve(size + 1);

    for (int n = 2; n <= size; n++) {
        // prime factorize
        std::vector<mf::PrimePower> factors = mf::prime_factorize(n, sieve.get());

        // find base idempotents
        const int num_idems = factors.size();
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
