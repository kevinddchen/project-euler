#include <array>

/*

First, for all integers up to 1,000,000 we compute how many matches are needed to write down the number without any
multiplication or addition operators.

Next, we allow multiplications: we iterate over all pairs a, b and check if c = a * b can be written with fewer matches
if we use a multiplication operator. If we iterate over a, b in the right way, then we can compute the optimal number of
matches in one pass of all pairs a, b.

Finally, we do the same with addition.

ANSWER 26688208

*/

constexpr std::array<int, 10> DIGIT_MATCH_COUNT = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

/**
 * Return the total number of matches needed to represent the number `n`.
 */
int get_match_count(int n)
{
    int sum = 0;
    while (n > 0) {
        const int digit = n % 10;
        sum += DIGIT_MATCH_COUNT[digit];
        n /= 10;
    }
    return sum;
}

long p893()
{
    constexpr int SIZE = 1'000'000;

    std::array<int, SIZE + 1> match_counts;

    // count matches, without any operations
    for (int n = 1; n <= SIZE; ++n) {
        match_counts[n] = get_match_count(n);
    }

    // count matches, allowing multiplication
    for (int a = 2; a <= SIZE / 2; ++a) {
        for (int b = 2; b <= a; ++b) {
            const int c = a * b;
            if (c > SIZE) {
                break;
            }

            const int c_matches = match_counts[a] + match_counts[b] + 2;
            if (c_matches < match_counts[c]) {
                match_counts[c] = c_matches;
            }
        }
    }

    // count matches, allowing multiplication and addition
    for (int a = 1; a <= SIZE; ++a) {
        for (int b = 1; b <= a; ++b) {
            const int c = a + b;
            if (c > SIZE) {
                break;
            }

            const int c_matches = match_counts[a] + match_counts[b] + 2;
            if (c_matches < match_counts[c]) {
                match_counts[c] = c_matches;
            }
        }
    }

    // done. compute sum.

    int T = 0;
    for (int n = 1; n <= SIZE; ++n) {
        T += match_counts[n];
    }

    return T;
}

int main()
{
    printf("%ld\n", p893());
}
