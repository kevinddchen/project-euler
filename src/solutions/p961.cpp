#include <array>

/*

It is more efficient to use a binary representation, which we call "pattern", e.g. 101, where "1" represents a non-zero
digit and "0" represents a zero digit. Once we determine that a given pattern can always be won, if the pattern has k
non-zero digits, then there are 9^k numbers which are represented by that pattern.

As for figuring out which patterns can always be won, we use dynamic programming to keep track of smaller patterns that
are winning. Then it is a simple matter of iterating through all the sub-patterns that can be obtained from a pattern by
removing digits, and checking if that sub-pattern is losing (in which case the original pattern can always be won). If
all sub-patterns are winning, then the original pattern is losing.

ANSWER 166666666689036288

*/

constexpr int LOG_N = 18;

constexpr size_t TABLE_SIZE = 2 << (LOG_N - 1);

/**
 * Figures out if a pattern is winning/losing, based on previously computed values. Strategy is to iterate through all
 * sub-patterns obtained by removing a single digit.
 */
bool is_win(uint64_t pattern, const std::array<bool, TABLE_SIZE>& win_table)
{
    uint64_t left = pattern;
    uint64_t right = 0;

    int right_size = 0;
    while (left > 0) {
        // remove smallest digit from left
        const uint64_t removed_digit = left & 1;
        left >>= 1;

        // check if sub-pattern formed from left concatenated with right is losing
        const uint64_t sub_pattern = (left << right_size) | right;
        if (!win_table[sub_pattern]) {
            return true;
        }

        // add removed digit to right
        right |= (removed_digit << right_size);
        ++right_size;
    }
    // if all sub-patterns are winning, then this pattern is losing
    return false;
}

/**
 * Given a pattern, count the number of possible numbers it represents.
 */
long count_representations(uint64_t pattern)
{
    // if `pattern` has k non-zero digits, then count = 9^k
    long count = 1;
    while (pattern > 0) {
        if (pattern & 1) {
            count *= 9;
        }
        pattern >>= 1;
    }
    return count;
}

long p961()
{
    /* Array tracking computed pattern -> win/lose values. */
    std::array<bool, TABLE_SIZE> win_table;
    win_table[0] = false;

    long count = 0;

    for (uint64_t pattern = 1; pattern < TABLE_SIZE; ++pattern) {
        win_table[pattern] = is_win(pattern, win_table);
        if (win_table[pattern]) {
            count += count_representations(pattern);
        }
    }

    return count;
}

int main()
{
    printf("%ld\n", p961());
}
