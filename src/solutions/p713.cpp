#include <cstdio>

/*

It is important to note that for a group of i fuses, we can test all
i * (i - 1) / 2 combinations of pairs to conclude that there are at least i - 1
blown fuses in the group.

So for N fuses, m of which are good, the goal is to divide the fuses into k
bins. Each bin containing b_i fuses requires b_i * (b_i - 1) / 2 tests to
conclude that there are at least b_i - 1 blown fuses in the bin. The objective
is to account for N - m + 1 blown fuses while minimizing the cost, and since we
account for one more blown fuse than we have, this gives the number of tests
required to ensure we pick a pair of good fuses.

Since:
    1) sum_i b_i = N
    2) sum_i (b_i - 1) = N - m + 1
we can note that k = m - 1.

Let us see this in practice for the T(8, 4) solution. Since k = 3, we have 3
bins. The minimum cost is to distribute the 8 fuses as evenly as possible into
{3, 3, 2}. The total number of tests is 3 + 3 + 1 = 7.

ANSWER 788626351539895

*/

/**
 * Number of tests is `num_fuses * (num_fuses - 1) / 2`.
 */
long num_tests(long num_fuses)
{
    return num_fuses * (num_fuses - 1) / 2;
}

long p713()
{
    const int N = 10'000'000;

    long total_tests = 0;
    for (int num_bins = 1; num_bins < N; num_bins++) {
        const long small_bin_size = N / num_bins;
        const long large_bin_size = small_bin_size + 1;

        const long num_large_bins = N % num_bins;
        const long num_small_bins = num_bins - num_large_bins;

        total_tests += num_small_bins * num_tests(small_bin_size);
        total_tests += num_large_bins * num_tests(large_bin_size);
    }
    return total_tests;
}

int main()
{
    printf("%ld\n", p713());
}
