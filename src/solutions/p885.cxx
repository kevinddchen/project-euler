#include "common.h"

#include <algorithm>
#include <array>
#include <functional>
#include <vector>

/*

ANSWER

*/

// long f(long x)
// {
//     // get non-zero digits of x
//     std::vector<long> digits;
//     while (x > 0) {
//         const auto dv = std::div(x, 10L);
//         if (dv.rem != 0) {
//             digits.push_back(dv.rem);
//         }
//         x = dv.quot;
//     }
//     // sort the digits
//     std::sort(digits.begin(), digits.end());
//     // from sorted digits, form the number
//     long result = 0;
//     for (auto digit : digits) {
//         result = 10 * result + digit;
//     }
//     return result;
// }

// long S(int num_digits)
// {
//     const long limit = std::pow(10, num_digits);
//     long sum = 0;
//     for (long x = 1; x < limit; ++x) {
//         sum += f(x);
//     }
//     return sum;
// }

/**
 * Compute factorial.
 */
long factorial(long n)
{
    long prod = 1;
    for (long i = 2; i <= n; ++i) {
        prod *= i;
    }
    return prod;
}

/**
 * Given a set of digits and their counts, compute the total number of
 * permutations, including leading zeros. This equals the multinomial
 * coefficient.
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

long S(int num_digits, long mod)
{
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


long p885()
{
    constexpr int num_digits = 18;
    constexpr long mod = 1123455689;

    return S(num_digits, mod);
}

int main()
{
    printf("%ld\n", p885());
}
