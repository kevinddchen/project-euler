#include "common.h"

#include <vector>

/*

One can show that f(n) equals the number of ordered binary trees we can draw:

f(0): -

f(1): 1

f(2): 2
      1

f(3): 3 ,  3
      2   2 1
      1

f(4): 4 ,   4 ,   4  ,   4  ,  4
      3    3     3 1    3 2   2 3
      2   2 1   2      1     1
      1

For f(n+1), we count the number of ordered binary trees we can construct by
taking a tree from f(k) and f(n-k) each and joining them under a new root node.
We also have some combinatorial factors having to do with relabelling the
numbers, but in the end we have the following recursion relation:

    2 * f(n+1) = sum_{k=0}^n (n choose k) * f(k) * f(n-k)

See: https://en.wikipedia.org/wiki/Alternating_permutation

ANSWER 773479144

*/

/**
 * Given array of n choose 0, n choose 1, ..., n choose n, compute array of
 * n+1 choose 0, n+1 choose 1, ..., n+1 choose n+1.
 */
void iterate_next_comb_mod(std::vector<int>& comb_mod_cache, int n, int M)
{
    int temp_a = comb_mod_cache[0];
    int temp_b;
    for (int i = 1; i < n; i++) {
        temp_b = comb_mod_cache[i];
        comb_mod_cache[i] = (temp_a + temp_b) % M;
        temp_a = temp_b;
    }
    comb_mod_cache[n] = 1;
}

long p709()
{
    const int M = 1'020'202'009;
    const int N = 24680;

    const int inv2 = 510'101'005;  // inverse of 2 mod M

    // Vector that caches values of n choose k mod M. Starts off with n=0,
    // and call `iterate_next_comb_mod` to get n=1, n=2, and so forth.
    std::vector<int> comb_mod(N + 1);
    comb_mod[0] = 1;

    // Vector caches values of f(n) mod M.
    std::vector<int> f(N + 1);
    f[0] = 1;
    f[1] = 1;

    for (int n = 1; n < N; n++) {
        // get values of n choose k mod M
        iterate_next_comb_mod(comb_mod, n, M);

        // get value of f(n+1)
        long sum = 0;
        for (int k = 0; k <= n; k++) {
            long x = ((long)comb_mod[k] * f[k]) % M;
            sum = (sum + x * f[n - k]) % M;
        }
        f[n + 1] = (sum * inv2) % M;
    }
    return f[N];
}

int main()
{
    TIMED(printf("%ld\n", p709()));
}
