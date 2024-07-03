#include "common.h"

#include <array>
#include <functional>

/*

Our strategy is to iterate over all choices of 18 digits, and then for each
choice, count the numbers formed by taking all permutations of digits. This
works because each choice of digits has a single unique representation for f().

ANSWER 827850196

*/

/**
 * Compute factorial. Slow, but good enough.
 */
long factorial(long n)
{
    assert(n < 20);  // likely can't compute factorials larger than this
    long prod = 1;
    for (long i = 2; i <= n; ++i) {
        prod *= i;
    }
    return prod;
}

/**
 * Given a set of digits and their counts, count the numbers formed by taking
 * all permutations of digits, including leading zeros. This equals the
 * multinomial coefficient.
 */
long num_permutations(const std::array<int, 10>& digit_counts, int num_digits)
{
    long coeff = factorial(num_digits);
    for (auto count : digit_counts) {
        coeff /= factorial(count);
    }
    return coeff;
}

/**
 * Given an array of digit counts, return the number where all the non-zero
 * digits are concatenated in increasing order.
 */
long digit_counts_to_number(const std::array<int, 10>& digit_counts)
{
    long result = 0;
    for (long d = 1; d < 10; ++d) {
        for (int c = 0; c < digit_counts[d]; ++c) {
            result = 10 * result + d;
        }
    }
    return result;
}

long p885()
{
    const int num_digits = 18;
    const long mod = 1123455689;

    long sum = 0;

    /**
     * Iterate over all choices of digits, using recursion.
     */
    std::function<void(int, int)> recurse;

    // `digit_counts[d]` equals number of digit `d` in the choice of digits
    std::array<int, 10> digit_counts;

    recurse = [&](int curr_count, int curr_digit) -> void {
        // stop condition
        if (curr_digit == 9) {
            // make all remaining digits 9s
            digit_counts[curr_digit] = num_digits - curr_count;

            const long number = digit_counts_to_number(digit_counts) % mod;
            const long num_perms = num_permutations(digit_counts, num_digits) % mod;
            sum = (sum + number * num_perms) % mod;
            return;
        }
        for (int i = 0; i <= num_digits - curr_count; ++i) {
            digit_counts[curr_digit] = i;
            recurse(curr_count + i, curr_digit + 1);
        }
    };

    recurse(0, 0);

    return sum;
}

int main()
{
    printf("%ld\n", p885());
}
