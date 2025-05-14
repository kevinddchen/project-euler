#include <mf/mathfuncs.hpp>

/*

In order to compute the 10^16th digit of A, we only need to compute 16 * ln(10)
/ ln(3) ~ 33.5 => 33 terms of the sum. We don't have to be too worried about
carry-over from later terms because they are exponentially smaller.

The digits of the decimal expansion of 1/3^i can be quickly calculated by
determining the modular power of 10 mod 3^i. We just have to be careful about
integer overflow when multiplying together large longs.

ANSWER 6086371427

*/

/**
 * Get the nth, n+1th, ..., n+mth digit of the decimal expansion of 1/k. n and
 * m must be greater than 0.
 *
 * Adapted from a similar function in Problem 820.
 */
std::vector<int> get_decimal_digits(long k, long n, long m)
{
    assert(n > 0);
    assert(m > 0);
    long x = mf::modular_power(10 % k, n - 1, k);  // this implementation prevents integer overflow

    std::vector<int> digits;
    for (int i = 0; i < m; i++) {
        x *= 10;
        digits.push_back(x / k);
        x %= k;
    }
    return digits;
}

long p731()
{
    const int n_log_10 = 16;
    const long n = mf::pow(10, n_log_10);

    const int num_digits = 10;
    // number of terms in the sum we have to consider; equals 33
    const int num_terms = n_log_10 * std::log(10) / std::log(3);
    // to account for carry-over in addition, we compute 10 digits + a few more
    // to account for the worst-case scenario, we compute 10 + `num_terms` digits
    const int adj_num_digits = num_digits + num_terms;

    // keeps track of the `10 + num_terms` digits, without carrying over
    std::vector<int> sum_digits;
    for (int i = 0; i < adj_num_digits; i++) {
        sum_digits.push_back(0);
    }

    long power_of_3 = 3;
    while (power_of_3 < n) {
        const long start_digit = n - power_of_3;  // account for 10^(3^i) factor
        const std::vector<int> digits = get_decimal_digits(power_of_3, start_digit, adj_num_digits);
        for (int i = 0; i < static_cast<int>(sum_digits.size()); i++) {
            sum_digits[i] += digits[i];
        }
        power_of_3 = power_of_3 * 3;
    }

    // do carry over
    int carry_over = 0;
    for (int i = adj_num_digits - 1; i >= 0; i--) {
        sum_digits[i] += carry_over;
        carry_over = sum_digits[i] / 10;
        sum_digits[i] %= 10;
    }

    long result = 0;
    for (int i = 0; i < num_digits; i++) {
        result = (result * 10 + sum_digits[i]);
    }
    return result;
}

int main()
{
    printf("%ld\n", p731());
}
