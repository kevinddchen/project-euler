#include "common.h"

#include <array>

#include <climits>

/*

More or less brute force: iterate over all "top vertices" and iterate over all
heights. Find the triangle with the smallest total sum. While this is naively
an O(n^4) algorithm, we can reduce it to O(n^3) by precomputing the partial sum
of each row. In this way, the sum over a sequence of elements in any particular
row can be done in one or two queries of this array of partial sums.

ANSWER -271248680

*/

/**
 * Linear Congruential Generator.
 */
class LinConGen
{
    long t;

public:
    LinConGen() { t = 0; }

    long next()
    {
        t = (615949L * t + 797807L) % 1048576L;
        return t - 524288L;
    }
};

/**
 * Get the flat index in the triangle given the (row, col) coordinates.
 * (0,0)                    0
 * (1,0) (1,1)          --> 1 2
 * (2,0) (2,1) (2,2)        3 4 5
 * ...                      ...
 */
inline int get_index(int row, int col)
{
    return row * (row + 1) / 2 + col;
}

long p150()
{
    const int rows = 1000;
    const int num_elems = rows * (rows + 1) / 2;

    // generate the triangle, as flat array
    LinConGen gen;
    std::array<long, num_elems> triangle;
    for (int i = 0; i < num_elems; i++) {
        triangle.at(i) = gen.next();
    }

    // generate partial sums of each row
    std::array<long, num_elems> partial_sums;
    for (int row = 0; row < rows; row++) {
        long sum = 0;
        int index = get_index(row, 0);
        for (int col = 0; col <= row; col++) {
            sum += triangle.at(index);
            partial_sums.at(index) = sum;
            index++;
        }
    }

    // find triangle with smallest sum
    long min_sum = LONG_MAX;

    // iterate through all triangle vertices
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col <= row; col++) {
            long sum = 0;
            // iterate through all triangle heights
            for (int height = 0; height < rows - row; height++) {
                const int left_index = get_index(row + height, col);
                const int right_index = left_index + height;

                sum += partial_sums.at(right_index);
                if (col > 0) {
                    sum -= partial_sums.at(left_index - 1);
                }

                if (sum < min_sum) {
                    min_sum = sum;
                }
            }
        }
    }

    return min_sum;
}

int main()
{
    TIMED(printf("%ld\n", p150()));
}
