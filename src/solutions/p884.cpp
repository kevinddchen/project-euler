#include <unordered_map>

#include <cassert>
#include <cmath>

/*

We can note that the values of D(n) for large enough n follow a simple pattern:

    D(n) = 1 + D(n - 64) , 64 <= n <= 124
    D(n) = 1 + D(n - 125) , 125 <= n <= 215
    D(n) = 1 + D(n - 216) , 216 <= n <= 342
    ...

and so on. We can use these recursion relations to efficiently compute values
of S(N). For instance,

S(125) = sum_{n=1}^124 D(n)
       = S(64) + D(64) + sum_{n=65}^124 D(n)
       = S(64) + 1 + sum_{n=1}^60 (1 + D(n))
       = S(64) + 61 + sum_{n=1}^60 D(n)

This generalizes to the following fact: if N > 64 and c is the largest cube
smaller than N, then

    S(N) = S(c) + S(N - c) + N - c

Thus if we compute S(M) for M = 1, 2, ..., 64 and 5^3, 6^3, ... up to N, we can
efficiently compute S(N).

ANSWER 1105985795684653500

*/

long cube(long x)
{
    return x * x * x;
}

/**
 * Returns integer cube root, rounded down.
 */
long icbrt(long x)
{
    long root = std::cbrtl(x);
    // account for floating point errors
    while (cube(root) > x) {
        --root;
    }
    while (cube(root + 1) <= x) {
        ++root;
    }
    return root;
}

/**
 * Computes D(n), slowly.
 */
long D(long n)
{
    long count = 0;
    while (n > 0) {
        n -= cube(icbrt(n));
        ++count;
    }
    return count;
}

/**
 * Computes S(N) but needs cached values of S(M) for M = 1, 2, 3, ..., 64 and
 * 5^3, 6^3, ... up to N.
 */
long S(long N, const std::unordered_map<long, long>& cache)
{
    long total = 0;
    while (N > 64) {
        // find largest cube less than N
        const long c = cube(icbrt(N - 1));
        // look up cached S(c)
        const auto S_c = cache.find(c);
        assert(S_c != cache.end());  // check cache-hit
        total += N - c + S_c->second;
        N -= c;
    }
    // now that N <= 64, we can look up cached S(N)
    const auto S_N = cache.find(N);
    assert(S_N != cache.end());  // check cache-hit
    total += S_N->second;
    return total;
}

long p884()
{
    const long target = 1e17;
    const long max_root = icbrt(1e17);

    // prepare values of S(N) for N = 1, 2, ..., 64
    std::unordered_map<long, long> cache;
    {
        long S_N = 0;
        for (long N = 1; N <= 64; ++N) {
            S_N += D(N - 1);
            cache.emplace(N, S_N);
        }
    }

    // prepare values of S(N) for N = 5^3, 6^3, ..., up to 10^17
    for (long root = 5; root <= max_root; ++root) {
        const long c = cube(root);
        const long S_c = S(c, cache);
        cache.emplace(c, S_c);
    }

    return S(target, cache);
}

int main()
{
    printf("%ld\n", p884());
}
