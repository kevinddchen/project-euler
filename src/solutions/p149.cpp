#include "mf/generators.hpp"

#include <vector>

#include <cassert>

/*

The maximum sum of a contiguous subarray of a list can be found using dynamic
programming. After that, it is just a matter of iterating over the rows,
columns, and diagonals of the grid.

This algorithm is O(n^2). The brute force algorithm is O(n^3) and isn't too
slow either.

ANSWER 52852124

*/

/**
 * Get row, where 0 <= row < size.
 */
std::vector<int> get_row(int row, const std::vector<int>& grid, int size)
{
    std::vector<int> row_vec;
    for (int col = 0; col < size; col++) {
        row_vec.push_back(grid[row * size + col]);
    }
    return row_vec;
}

/**
 * Get column, where 0 <= col < size.
 */
std::vector<int> get_col(int col, const std::vector<int>& grid, int size)
{
    std::vector<int> col_vec;
    for (int row = 0; row < size; row++) {
        col_vec.push_back(grid[row * size + col]);
    }
    return col_vec;
}

/**
 * Get forward slash diagonal, where 0 <= col_plus_row < 2 * size - 1.
 */
std::vector<int> get_forward_slash(int col_plus_row, const std::vector<int>& grid, int size)
{
    std::vector<int> slash_vec;
    for (int row = 0; row < size; row++) {
        int col = col_plus_row - row;
        if (col < 0 || col >= size) {
            continue;
        }
        slash_vec.push_back(grid[row * size + col]);
    }
    return slash_vec;
}

/**
 * Get back slash diagonal, where -size + 1 <= col_minus_row < size.
 */
std::vector<int> get_back_slash(int col_minus_row, const std::vector<int>& grid, int size)
{
    std::vector<int> slash_vec;
    for (int row = 0; row < size; row++) {
        int col = col_minus_row + row;
        if (col < 0 || col >= size) {
            continue;
        }
        slash_vec.push_back(grid[row * size + col]);
    }
    return slash_vec;
}

/**
 * Find the maximum sum of a contiguous subarray of a list. Uses dynamic
 * programming.
 */
long find_max_subsum(const std::vector<int>& list)
{
    assert(list.size() > 0);
    long max_using_last = list[0];
    long max = list[0];
    for (int i = 1; i < static_cast<int>(list.size()); i++) {
        max_using_last = std::max(0L, max_using_last) + list[i];
        max = std::max(max, max_using_last);
    }
    return max;
}

long p149()
{
    const int size = 2000;

    // populate grid values
    mf::LaggedFibonacci gen;
    std::vector<int> grid(size * size);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            grid[row * size + col] = *gen++ - 500'000;
        }
    }

    // find max subsum in each row, col, and diagonal
    long max_sum = 0;

    for (int row = 0; row < size; row++) {
        const std::vector<int> row_vec = get_row(row, grid, size);
        const long sum = find_max_subsum(row_vec);
        if (sum > max_sum) {
            max_sum = sum;
        }
    }

    for (int col = 0; col < size; col++) {
        const std::vector<int> col_vec = get_col(col, grid, size);
        const long sum = find_max_subsum(col_vec);
        if (sum > max_sum) {
            max_sum = sum;
        }
    }

    for (int col_plus_row = 0; col_plus_row < 2 * size - 1; col_plus_row++) {
        const std::vector<int> slash_vec = get_forward_slash(col_plus_row, grid, size);
        const long sum = find_max_subsum(slash_vec);
        if (sum > max_sum) {
            max_sum = sum;
        }
    }

    for (int col_minus_row = -size + 1; col_minus_row < size; col_minus_row++) {
        const std::vector<int> slash_vec = get_back_slash(col_minus_row, grid, size);
        const long sum = find_max_subsum(slash_vec);
        if (sum > max_sum) {
            max_sum = sum;
        }
    }

    return max_sum;
}

int main()
{
    printf("%ld\n", p149());
}
