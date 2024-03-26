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

long p0()
{
    std::array<std::array<int, 10>, SEQ_LEN> counts;
    for (size_t i = 0; i < SEQ_LEN; ++i) {
        counts[i].fill(0);
    }

    for (const auto& guess : GUESSES) {
        for (size_t i = 0; i < SEQ_LEN; ++i) {
            counts[i][guess[i]] += 1;
        }
    }

    for (size_t i = 0; i < SEQ_LEN; ++i) {
        for (size_t j = 0; j < 10; ++j) {
            printf("%d ", counts[i][j]);
        }
        printf("\n");
    }

    int sum_correct = 0;
    for (const auto& guess : GUESSES) {
        sum_correct += guess[SEQ_LEN];
    }
    printf("total correct: %d\n", sum_correct);
}

int main()
{
    printf("%ld\n", p0());
}
