#include "common.h"
#include "generators.h"

#include <array>
#include <vector>

/*

This can be calculated by a modified version of the "quickselect" algorithm.

We first sort the sequence s_i in O(n log n) time. Then for each s_i, we keep
track of a range of indices [i+1, n) that represent possible indices for j in
the product s_i * s_j. Each iteration of the quickselect algorithm, we pick a
random pivot. For each s_i, we find the slice in the range corresponding to the
pivot. This can be done efficiently with binary search, and will take O(n log
n) time in total. Then based on the number of products less than the pivot, we
either pick the upper half or lower half and update the ranges.

This can be repeated until the number of products is small enough to brute
force.

ANSWER 475808650131120

*/

inline long ceil_div(long a, long b)
{
    return 1 + (a - 1) / b;
}

/**
 * Pick a pivot for the "quickselect" algorithm.
 */
template <size_t n>
long pick_pivot(const std::array<long, n>& sequence, const std::vector<std::array<int, 2>>& ranges)
{
    // randomly pick an i with a non-empty range
    int i;
    while (true) {
        i = std::rand() % (n - 1);
        if (ranges[i][0] != ranges[i][1]) {
            break;
        }
    }
    // randomly pick a j in the range
    const int j = ranges[i][0] + std::rand() % (ranges[i][1] - ranges[i][0]);

    return sequence[i] * sequence[j];
}

/**
 * One iteration of the "quickselect" algorithm.
 *
 * @param sequence the sorted sequence of s_i
 * @param ranges the ranges of each s_i
 * @param median_index the index of the median
 * @param pivot the chosen pivot
 * @returns the updated number of products in the ranges
 */
template <size_t n>
long iteration(
    const std::array<long, n>& sequence, std::vector<std::array<int, 2>>& ranges, long& median_index, long pivot)
{
    assert(ranges.size() == n - 1);

    long count_lt_pivot = 0;

    // find the slice of the pivot in each range
    std::vector<int> slices;
    for (int i = 0; i < n - 1; i++) {
        // if range is empty, skip
        if (ranges[i][0] == ranges[i][1]) {
            slices.push_back(ranges[i][0]);
            continue;
        }
        const long* left = sequence.begin() + ranges[i][0];
        const long* right = sequence.begin() + ranges[i][1];
        const long target = ceil_div(pivot, sequence[i]);
        const long* slice = std::lower_bound(left, right, target);
        // note that: *(slice - 1) * sequence[i] < pivot <= *slice * sequence[i]
        slices.push_back(slice - sequence.begin());
        count_lt_pivot += slices[i] - ranges[i][0];
    }

    bool pick_upper_half = false;
    if (count_lt_pivot <= median_index) {
        median_index -= count_lt_pivot;
        pick_upper_half = true;
    }

    long new_num_products = 0;
    for (int i = 0; i < n - 1; i++) {
        if (pick_upper_half) {
            ranges[i][0] = slices[i];  // set left to slice
        } else {
            // TODO: do we want to include the pivot in the range?
            ranges[i][1] = slices[i];  // set right to slice
        }
        new_num_products += ranges[i][1] - ranges[i][0];
    }

    return new_num_products;
}

/**
 * Find median by brute force.
 *
 * @param sequence the sorted sequence of s_i
 * @param ranges the ranges of each s_i
 * @param median_index the index of the median
 * @returns the median value
 */
template <size_t n>
long brute_force(const std::array<long, n>& sequence, const std::vector<std::array<int, 2>>& ranges, long& median_index)
{
    assert(ranges.size() == n - 1);

    std::vector<long> products;
    for (int i = 0; i < n - 1; i++) {
        for (int j = ranges[i][0]; j < ranges[i][1]; j++) {
            products.push_back(sequence[i] * sequence[j]);
        }
    }
    std::sort(products.begin(), products.end());
    return products[median_index];
}

long p793()
{
    std::srand(42);

    const long n = 1'000'003;

    long num_products = (n * (n - 1)) / 2;  // initially odd number
    long median_index = (num_products - 1) / 2;

    // initialize s_i and sort
    std::array<long, n> sequence;
    {
        mf::BlumBlumShub bbs;
        for (int i = 0; i < n; i++) {
            sequence[i] = *bbs++;
        }
        std::sort(sequence.begin(), sequence.end());
    }

    // initialize ranges
    // 0: [1, n], 1: [2, n], ..., n - 2: [n - 1, n]
    std::vector<std::array<int, 2>> ranges;
    for (int i = 0; i < n - 1; i++) {
        ranges.push_back({i + 1, n});
    }

    long pivot;
    while (num_products > 100) {
        pivot = pick_pivot(sequence, ranges);
        num_products = iteration(sequence, ranges, median_index, pivot);
    }

    return brute_force(sequence, ranges, median_index);
}

int main()
{
    TIMED(printf("%ld\n", p793()));
}
