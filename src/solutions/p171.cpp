#include "mf/mathfuncs.hpp"

#include <array>

/*

We iterate over all choices of digits. For each choice of digits, we first check if the square sum of those digits is a
perfect square itself. If true, then we can compute the sum of all numbers matching that choice of digits. This just
involves some combinatorics.

ANSWER 142989277

*/

constexpr long MOD = 1e9;

constexpr int DIGITS = 20;

/**
 * Returns 111...1 (n digits long).
 */
long repunit(int n)
{
    long sum = 0;
    long unit = 1;
    for (long i = 0; i < n; ++i) {
        sum += unit;
        unit *= 10;
    }
    return sum;
}

/**
 * Check if n is a perfect square.
 *
 * This implementation is good enough for our purposes.
 */
bool is_square(long n)
{
    const long root = static_cast<long>(std::round(std::sqrt(static_cast<double>(n))));
    return root * root == n;
}

long p171()
{
    // compute factorials
    std::array<long, DIGITS + 1> factorial;
    factorial[0] = 1;
    for (long i = 1; i <= DIGITS; ++i) {
        factorial[i] = i * factorial[i - 1];
    }

    long sum = 0;

    // HACK: the nested for loops is ugly as hell, but sure beats some confusing recursive function

    // let `di` denote number of times the digit `i` appears
    // iterate over all digit choices, where d0 + d1 + ... + d9 = DIGITS
    for (int d0 = 0; d0 <= DIGITS; ++d0) {
        const int r0 = DIGITS - d0;
        for (int d1 = 0; d1 <= r0; ++d1) {
            const int r1 = r0 - d1;
            for (int d2 = 0; d2 <= r1; ++d2) {
                const int r2 = r1 - d2;
                for (int d3 = 0; d3 <= r2; ++d3) {
                    const int r3 = r2 - d3;
                    for (int d4 = 0; d4 <= r3; ++d4) {
                        const int r4 = r3 - d4;
                        for (int d5 = 0; d5 <= r4; ++d5) {
                            const int r5 = r4 - d5;
                            for (int d6 = 0; d6 <= r5; ++d6) {
                                const int r6 = r5 - d6;
                                for (int d7 = 0; d7 <= r6; ++d7) {
                                    const int r7 = r6 - d7;
                                    for (int d8 = 0; d8 <= r7; ++d8) {
                                        const int d9 = r7 - d8;

                                        // compute square sum of digits
                                        const long square_sum_of_digits = d1 + 4 * d2 + 9 * d3 + 16 * d4 + 25 * d5 +
                                                                          36 * d6 + 49 * d7 + 64 * d8 + 81 * d9;

                                        if (!is_square(square_sum_of_digits)) {
                                            continue;
                                        }

                                        // compute sum of all numbers with this combination of digits
                                        long multiplicity = factorial[DIGITS];
                                        multiplicity /= factorial[d0];
                                        multiplicity /= factorial[d1];
                                        multiplicity /= factorial[d2];
                                        multiplicity /= factorial[d3];
                                        multiplicity /= factorial[d4];
                                        multiplicity /= factorial[d5];
                                        multiplicity /= factorial[d6];
                                        multiplicity /= factorial[d7];
                                        multiplicity /= factorial[d8];
                                        multiplicity /= factorial[d9];

                                        multiplicity *=
                                            d1 + 2 * d2 + 3 * d3 + 4 * d4 + 5 * d5 + 6 * d6 + 7 * d7 + 8 * d8 + 9 * d9;
                                        multiplicity /= DIGITS;

                                        sum += mf::modular_product(multiplicity % MOD, repunit(DIGITS) % MOD, MOD);
                                        sum %= MOD;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return sum;
}

int main()
{
    // printf("%ld\n", p0());
    printf("%ld\n", p171());
}
