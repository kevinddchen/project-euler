#include "common.h"
#include "mathfuncs.h"

#include <algorithm>
#include <array>

#include <cmath>

/*

If we have numbers {2, 3, ..., N} which are raised to the power of 2^k, note
that instead of comparing values of n^(2^k) directly, we can instead compare
values of k + log2(log2(n)), since log2 is a monotonic function. So we have an
array of these k + log2(log2(n)) values, and we increment the smallest value by
1 and repeat 10^16 times.

Once all k + log2(log2(n)) values in the set are roughly equal, then the
pattern of "which value is the smallest" becomes cyclic. This makes the final
value of k for each n easy to calculate.

ANSWER 950591530

*/

long p822()
{
    const long N = 10'000;                  // maximum value of n
    const long M = 10'000'000'000'000'000;  // maximum value of m
    const long mod = 1234567891;

    // for each n, find the smallest value of k such that n^(2^k) >= N
    // or equivalently, k >= log2(log2(N)) - log2(log2(n))

    long total_k = 0;
    std::array<long, N - 1> k;

    for (int i = 0; i < N - 1; i++) {
        const int n = i + 2;
        k[i] = std::ceil(std::log2(std::log2(N)) - std::log2(std::log2(n)));
        total_k += k[i];
    }

    // we need to bring `total_k` up so that `M - total_k` is a multiple of `N - 1`
    // we do this by incrementing `k` for the smallest values of `k + log2(log2(n))`
    // this should not take too long, O(N log N) to sort the list.

    {
        assert(M >= total_k);
        const int num_increments = (M - total_k) % (N - 1);

        std::array<int, N - 1> indices;
        std::array<double, N - 1> k_plus_log2_log2_n;
        for (int i = 0; i < N - 1; i++) {
            const int n = i + 2;
            indices[i] = i;
            k_plus_log2_log2_n[i] = k[i] + std::log2(std::log2(n));
        }

        // sort indices based on the value of k_plus_log2_log2_n
        std::sort(indices.begin(), indices.end(), [&k_plus_log2_log2_n](int a, int b) {
            return k_plus_log2_log2_n[a] < k_plus_log2_log2_n[b];
        });

        for (int i = 0; i < num_increments; i++) {
            k[indices[i]]++;
        }
        total_k += num_increments;
    }

    // now all k are increased by the same amount
    {
        assert((M - total_k) % (N - 1) == 0);
        const long equal_increment = (M - total_k) / (N - 1);
        for (int i = 0; i < N - 1; i++) {
            k[i] += equal_increment;
        }
    }

    // compute the result
    // to compute n^(2^k) mod p, we use Fermi's little theorem because
    // p = 1234567891 is a prime. So we first compute 2^k mod (p - 1).
    long result = 0;
    for (int i = 0; i < N - 1; i++) {
        const long n = i + 2;
        const long power_of_2 = mf::modular_power(2, k[i], mod - 1);
        const long power_of_n = mf::modular_power(n, power_of_2, mod);
        result = (result + power_of_n) % mod;
    }

    return result;
}

int main()
{
    TIMED(printf("%ld\n", p822()));
}
