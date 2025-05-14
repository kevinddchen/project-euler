#include <vector>

/*

Similar to Problem 250: keep a 2D array `counts` whose (n, i)th element
represents the number of subsets with n elements whose sum equals i. Start with
all elements equal zero, except `counts[0][0] = 1` for the empty set. For each
k = 1^2, 2^2, ..., 100^2, update the array according to the rule:

    new_counts[n, i] = counts[n, i] + counts[n - 1, i - k]

The answer is the sum of i where `counts[50, i] == 1`. All that remains is to
figure out the dimensions for this array. The first dimension should be 50 + 1,
and the second dimension should be (51^2 + 52^2 + ... + 100^2) + 1, since that
is one greater than the largest sum for a subset of 50 elements. It turns out
the array has dimensions roughly equal to 50 x 300,000, which is not too bad.

ANSWER 115039000

*/

long p201()
{
    constexpr int size = 50;  // target size of subsets

    std::vector<int> set;  // set of all numbers
    for (int i = 1; i <= 100; ++i) {
        set.push_back(i * i);
    }

    // first, determine max sum 51^2 + 52^2 + ... + 100^2. this will be a
    // dimension of the `counts` array.
    int max_sum = 0;
    for (int i = set.size() - size; i < static_cast<int>(set.size()); ++i) {
        const int elem = set[i];
        max_sum += elem;
    }

    // counts[n][i] = number of sets of n elements that sum to i. we use floats
    // since we only care in the end if `counts[n][i] == 1`.
    std::vector<std::vector<float>> counts;
    for (int n = 0; n <= size; ++n) {
        counts.push_back(std::vector<float>(max_sum + 1, 0.0f));
    }
    counts[0][0] = 1.0f;

    for (int elem : set) {
        // perform counts[n][i] <- counts[n][i] + counts[n - 1][i - elem]. this
        // can be done in-place of we iterate over n in decreasing order
        for (int n = size; n > 0; --n) {
            for (int i = elem; i <= max_sum; ++i) {
                counts[n][i] += counts[n - 1][i - elem];
            }
        }
    }

    // sum i for counts[size][i] == 1
    int sum = 0;
    for (int i = 0; i <= max_sum; ++i) {
        if (counts[size][i] == 1.0f) {
            sum += i;
        }
    }

    return sum;
}

int main()
{
    printf("%ld\n", p201());
}
