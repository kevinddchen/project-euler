#include "mf/mathfuncs.hpp"

/*

Use dynamic programming. If you know all values of p(n, k) for some n, then by
computing the sequence n+1 --> pi(n+1) --> pi(pi(n+1)) --> ... --> 1, you can
compute all values of p(n+1, k).

ANSWER 172023848

*/

long p609()
{
    const int limit = 100'000'000;
    const int mod = 1'000'000'007;

    // get prime sieve
    const auto sieve = mf::prime_sieve(limit + 1);

    // compute prime counting function
    std::vector<int> pi(limit + 1);
    int count = 0;
    for (int i = 2; i <= limit; ++i) {
        if (sieve[i]) {
            count++;
        }
        pi[i] = count;
    }

    assert(pi[1] == 0);
    assert(pi[2] == 1);
    assert(pi[3] == 2);

    // compute p(n, k) via dynamic programming
    std::vector<int> p_k = {};
    for (int n = 1; n <= limit; n++) {
        int u = n;
        int k = sieve[u] ? 0 : 1;
        while (u != 1) {
            u = pi[u];
            if (!sieve[u]) {
                k++;
            }
            // increment p_k[k]
            while (static_cast<int>(p_k.size()) <= k) {
                p_k.push_back(0);
            }
            p_k[k]++;
        }
    }

    // compute product of non-zero elements of `p_k`
    long prod = 1;
    for (int p : p_k) {
        if (p == 0) {
            continue;
        }
        prod = (prod * static_cast<long>(p)) % mod;
    }

    return prod;
}

int main()
{
    printf("%ld\n", p609());
}
