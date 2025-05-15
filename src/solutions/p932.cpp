#include <cstdio>

/*

Since 2025-numbers are square, its simple to iterate over all squares with up to 16 digits. For each square, we simply
iterate over all ways to split its digits into a and b, and check that their sum equals what we want.

ANSWER 72673459417881349

*/


long p932()
{
    constexpr long LIMIT = 1e8;

    long sum = 0;

    // we iterate over values of `a + b`, which we call `i`
    for (long i = 1; i < LIMIT; ++i) {
        const long square = i * i;

        long a = square;
        long b = 0;
        long b_next_place = 1;

        while (a >= 10) {
            // take the ones digit from `a` and add it to the front of `b`.
            // `b_next_place` tracks the power of 10 at the front of `b`.
            const long a_ones_digit = a % 10;
            b += a_ones_digit * b_next_place;

            b_next_place *= 10;
            a /= 10;

            // skip if the digit is a 0
            if (a_ones_digit == 0) {
                continue;
            }

            if (a + b == i) {
                sum += square;
            }
        }
    }

    return sum;
}

int main()
{
    printf("%ld\n", p932());
}
