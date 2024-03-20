#include "common.h"
#include "mathfuncs.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <queue>

/*

ANSWER

*/

// static const size_t SEQ_LEN = 5;
// static const std::array<std::array<uint8_t, SEQ_LEN + 1>, 6> GUESSES = {{
//     {9, 0, 3, 4, 2, 2},
//     {7, 0, 7, 9, 4, 0},
//     {3, 9, 4, 5, 8, 2},
//     {3, 4, 1, 0, 9, 1},
//     {5, 1, 5, 4, 5, 2},
//     {1, 2, 5, 3, 1, 1},
// }};

// clang-format off
static const size_t SEQ_LEN = 16;
static const std::array<std::array<uint8_t, SEQ_LEN + 1>, 22> GUESSES = {{
    {5, 6, 1, 6, 1, 8, 5, 6, 5, 0, 5, 1, 8, 2, 9, 3, 2},
    {3, 8, 4, 7, 4, 3, 9, 6, 4, 7, 2, 9, 3, 0, 4, 7, 1},
    {5, 8, 5, 5, 4, 6, 2, 9, 4, 0, 8, 1, 0, 5, 8, 7, 3},
    {9, 7, 4, 2, 8, 5, 5, 5, 0, 7, 0, 6, 8, 3, 5, 3, 3},
    {4, 2, 9, 6, 8, 4, 9, 6, 4, 3, 6, 0, 7, 5, 4, 3, 3},
    {3, 1, 7, 4, 2, 4, 8, 4, 3, 9, 4, 6, 5, 8, 5, 8, 1},
    {4, 5, 1, 3, 5, 5, 9, 0, 9, 4, 1, 4, 6, 1, 1, 7, 2},
    {7, 8, 9, 0, 9, 7, 1, 5, 4, 8, 9, 0, 8, 0, 6, 7, 3},
    {8, 1, 5, 7, 3, 5, 6, 3, 4, 4, 1, 1, 8, 4, 8, 3, 1},
    {2, 6, 1, 5, 2, 5, 0, 7, 4, 4, 3, 8, 6, 8, 9, 9, 2},
    {8, 6, 9, 0, 0, 9, 5, 8, 5, 1, 5, 2, 6, 2, 5, 4, 3},
    {6, 3, 7, 5, 7, 1, 1, 9, 1, 5, 0, 7, 7, 0, 5, 0, 1},
    {6, 9, 1, 3, 8, 5, 9, 1, 7, 3, 1, 2, 1, 3, 6, 0, 1},
    {6, 4, 4, 2, 8, 8, 9, 0, 5, 5, 0, 4, 2, 7, 6, 8, 2},
    {2, 3, 2, 1, 3, 8, 6, 1, 0, 4, 3, 0, 3, 8, 4, 5, 0},
    {2, 3, 2, 6, 5, 0, 9, 4, 7, 1, 2, 7, 1, 4, 4, 8, 2},
    {5, 2, 5, 1, 5, 8, 3, 3, 7, 9, 6, 4, 4, 3, 2, 2, 2},
    {1, 7, 4, 8, 2, 7, 0, 4, 7, 6, 7, 5, 8, 2, 7, 6, 3},
    {4, 8, 9, 5, 7, 2, 2, 6, 5, 2, 1, 9, 0, 3, 0, 6, 1},
    {3, 0, 4, 1, 6, 3, 1, 1, 1, 7, 2, 2, 4, 6, 3, 5, 3},
    {1, 8, 4, 1, 2, 3, 6, 4, 5, 4, 3, 2, 4, 5, 8, 9, 3},
    {2, 6, 5, 9, 8, 6, 2, 6, 3, 7, 3, 1, 6, 8, 6, 7, 2},
}};
// clang-format on

/**
 * Check if a sequence satisfies all the guesses.
 */
bool check_sequence(const std::array<uint8_t, SEQ_LEN>& sequence)
{
    for (auto const& guess : GUESSES) {
        int num_correct = 0;
        for (int i = 0; i < SEQ_LEN; ++i) {
            if (sequence[i] == guess[i]) {
                ++num_correct;
            }
        }
        if (num_correct != guess[SEQ_LEN]) {
            return false;
        }
    }
    return true;
}

/**
 * `cooccurrences[i][j]` equals the number of "corrects" that digit j has
 * co-occurred with in position i.
 */
std::array<std::array<int, 10>, SEQ_LEN> get_cooccurrences()
{
    std::array<std::array<int, 10>, SEQ_LEN> cooccurrences;

    // initialize zero
    for (int i = 0; i < SEQ_LEN; ++i) {
        cooccurrences[i].fill(0);
    }

    // count co-occurrences for each guess
    for (auto const& guess : GUESSES) {
        int num_correct = guess[SEQ_LEN];
        // if `num_correct==0`, then we use a very negative co-occurrence to
        // prevent the digit from being used at all
        if (num_correct == 0) {
            num_correct = -1000;
        }
        for (int i = 0; i < SEQ_LEN; ++i) {
            cooccurrences[i][guess[i]] += num_correct;
        }
    }

    return cooccurrences;
}

/**
 * `sorted_idx_to_digit[i][j]` equals the digit with the jth highest
 * co-occurrence in position i.
 */
std::array<std::array<uint8_t, 10>, SEQ_LEN> sorted_cooccurrences_mapping(
    const std::array<std::array<int, 10>, SEQ_LEN>& cooccurrences)
{
    std::array<std::array<uint8_t, 10>, SEQ_LEN> sorted_idx_to_digit;

    for (int i = 0; i < SEQ_LEN; ++i) {
        std::iota(sorted_idx_to_digit[i].begin(), sorted_idx_to_digit[i].end(), 0);
        std::stable_sort(
            sorted_idx_to_digit[i].begin(), sorted_idx_to_digit[i].end(), [&cooccurrences, i](int a, int b) {
                return cooccurrences[i][a] > cooccurrences[i][b];
            });
    }

    return sorted_idx_to_digit;
}

/**
 * Holds a sequence as digits and as indices for those digits when sorted by
 * co-occurances. `total_occurrences` is the cum of all co-occurrences over all
 * digits. `last_updated_idx` is to prevent us from traversing the same
 * sequence multiple times.
 */
struct Sequence {
    std::array<uint8_t, SEQ_LEN> indices;
    std::array<uint8_t, SEQ_LEN> digits;
    int total_cooccurences;
    int last_updated_idx;

    Sequence(
        std::array<uint8_t, SEQ_LEN>&& sequence_idxs,
        const std::array<std::array<uint8_t, 10>, SEQ_LEN>& sorted_idx_to_digit,
        const std::array<std::array<int, 10>, SEQ_LEN>& cooccurrences,
        int last_updated_idx = 0)
        : indices(sequence_idxs),
          last_updated_idx(last_updated_idx)
    {
        // first, compute digits
        for (int i = 0; i < SEQ_LEN; ++i) {
            digits[i] = sorted_idx_to_digit[i][indices[i]];
        }

        // second, compute total co-occurrences
        total_cooccurences = 0;
        for (int i = 0; i < SEQ_LEN; ++i) {
            total_cooccurences += cooccurrences[i][digits[i]];
        }
    }

    bool operator<(const Sequence& other) const { return total_cooccurences < other.total_cooccurences; }
};

/**
 * Convert integer to array of digits. The 0th digit is the most significant.
 */
// std::array<uint8_t, SEQ_LEN> integer_to_digits(long n)
// {
//     std::array<uint8_t, SEQ_LEN> digits;
//     for (int i = SEQ_LEN - 1; i >= 0; --i) {
//         digits[i] = n % 10;
//         n /= 10;
//     }
//     assert(n == 0);
//     return digits;
// }

long p0()
{
    // const long limit = mf::pow(10, SEQ_LEN);
    // for (long i = 0; i < limit; ++i) {
    //     const auto digits = integer_to_digits(i);
    //     if (check_answer(digits)) {
    //         return i;
    //     }
    // }

    // first, compute table of co-occurrences
    const auto cooccurrences = get_cooccurrences();
    for (int i = 0; i < SEQ_LEN; ++i) {
        for (int j = 0; j < 10; ++j) {
            printf("%d:%d ", j, cooccurrences[i][j]);
        }
        printf("\n");
    }

    // second, sort digits by decreasing co-occurrences
    std::array<std::array<uint8_t, 10>, SEQ_LEN> sorted_idx_to_digit = sorted_cooccurrences_mapping(cooccurrences);
    for (int i = 0; i < SEQ_LEN; ++i) {
        for (int j = 0; j < 10; ++j) {
            printf("%d ", sorted_idx_to_digit[i][j]);
        }
        printf("\n");
    }

    // third, do BFS on total cooccurrence
    std::priority_queue<Sequence> sequences;
    {
        std::array<uint8_t, SEQ_LEN> zero_idxs;
        zero_idxs.fill(0);
        Sequence initial_sequence(std::move(zero_idxs), sorted_idx_to_digit, cooccurrences);
        sequences.push(std::move(initial_sequence));
    }

    while (!sequences.empty()) {
        const auto sequence = sequences.top();
        sequences.pop();

        // for (int i = 0; i < SEQ_LEN; ++i) {
        //     printf("%d", sequence.indices[i]);
        // }
        // printf(",");
        // for (int i = 0; i < SEQ_LEN; ++i) {
        //     printf("%d", sequence.digits[i]);
        // }

        // printf(" . %d", sequence.total_cooccurences);
        // printf("\n");

        // check sequence
        if (check_sequence(sequence.digits)) {
            for (int i = 0; i < SEQ_LEN; ++i) {
                printf("%d", sequence.digits[i]);
            }
            printf("\n");
            return 0;
        }

        // add children to stack
        for (int i = sequence.last_updated_idx; i < SEQ_LEN; ++i) {
            if (sequence.indices[i] == 9) {
                continue;
            }

            auto next_sequence_idxs = sequence.indices;  // copy
            next_sequence_idxs[i] += 1;
            Sequence next_sequence(std::move(next_sequence_idxs), sorted_idx_to_digit, cooccurrences, i);
            sequences.push(std::move(next_sequence));
        }
    }
    return 1;
}

int main()
{
    printf("%ld\n", p0());
}
