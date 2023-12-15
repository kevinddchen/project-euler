#include "common.h"
#include "mathfuncs.h"

/*

Not too bad by brute force. For each number of digits, we count the number of
dominating numbers. If n digits are equal, there are three cases:
1) n digits contain the first digit, and are nonzero
2) n digits do not contain the first digit, and are nonzero
3) n digits do not contain the first digit, and are zero

ANSWER 471745499

*/

/**
 * Given array of n choose 0, n choose 1, ..., n choose n, compute array of
 * n+1 choose 0, n+1 choose 1, ..., n+1 choose n+1.
 *
 * Taken from Problem 709.
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

/**
 * Compute the number of dominating numbers with exactly `num_digits` digits.
 * `comb_mod_cache` is an array of n choose k for `n = num_digits - 1`.
 */
long count_dominating_numbers(int num_digits, const std::vector<int>& comb_mod, long mod)
{
    long count = 9;  // all digits are the same
    for (int i = 1; 2 * i < num_digits; i++) {
        // `num_digits - i` digits the same

        // a) same digits includes first place; nonzero
        // from `num_digits - 1` positions pick `num_digits - i - 1` to be same (9)
        // remaining `i` digits possibly zero (9^i)
        count = (count + comb_mod[num_digits - 1 - i] * mf::modular_power(9, i + 1, mod)) % mod;

        // b) same digits does not include first place; nonzero
        // from `num_digits - 1` positions pick `num_digits - i` to be same (9)
        // first digit potentially nonzero (8)
        // remaining `i - 1` digits possibly zero (9^(i-1))
        count = (count + comb_mod[num_digits - i] * 8 * mf::modular_power(9, i, mod)) % mod;

        // c) same digits does not include first place; zero
        // from `num_digits - 1` positions pick `num_digits - i` to be same (1)
        // remaining `i` digits nonzero (9^i)
        count = (count + comb_mod[num_digits - i] * mf::modular_power(9, i, mod)) % mod;
    }
    return count;
}

long p788()
{
    const long mod = 1'000'000'007;
    const int N = 2022;

    // Vector that caches values of n choose k mod M. Starts off with n=0,
    // and call `iterate_next_comb_mod` to get n=1, n=2, and so forth.
    std::vector<int> comb_mod(N + 1);
    comb_mod[0] = 1;

    long total = 0;
    for (int num_digits = 1; num_digits <= N; num_digits++) {
        total = (total + count_dominating_numbers(num_digits, comb_mod, mod)) % mod;
        iterate_next_comb_mod(comb_mod, num_digits, mod);
    }

    return total;
}

int main()
{
    printf("%ld\n", p788());
}
