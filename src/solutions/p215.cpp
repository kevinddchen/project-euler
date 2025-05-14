#include <Eigen/Dense>

#include <vector>

/*

Let f(i) be the number of ways to fill a row of width i with bricks of size 2
or 3. We first note that it follows the recursion,

    f(i) = f(i-2) + f(i-3)

Since f(32) = 3329, it isn't that bad to determine all the rows explicitly and
for each pair of rows figure out if there is a crack between them. Doing this
gives us a 3329 x 3329 transition matrix, where the (i, j) entry is 1 if there
is no crack between the ith and jth brick rows, and 0 otherwise.

Note that if we start with the state {1, 0, ..., 0} representing a particular
brick row, one application of the transition matrix will give us the possible
brick rows that can be placed on top of it. Repeated applications of the
transition matrix will give us the number of ways to fill the wall.

Since everything is linear, we can start with the state {1, 1, ..., 1} and
apply the transition matrix 9 times. If we sum the entries of the resultant
vector, we get the total number of walls we can construct.

ANSWER 806844323190414

*/

using MatrixXl = Eigen::Matrix<long, Eigen::Dynamic, Eigen::Dynamic>;
using VectorXl = Eigen::Matrix<long, Eigen::Dynamic, 1>;

/**
 * Returns the ways to fill a row of the given width with bricks of size 2 and
 * 3.
 */
std::vector<std::vector<int>> get_brick_rows(int width)
{
    assert(width >= 3);

    std::vector<std::vector<int>> fm3 = {};     // tracks f(i-3)
    std::vector<std::vector<int>> fm2 = {{2}};  // tracks f(i-2)
    std::vector<std::vector<int>> fm1 = {{3}};  // tracks f(i-1)

    for (int i = 4; i <= width; ++i) {
        std::vector<std::vector<int>> f;

        // for each element in f(i-3), append 3
        for (const auto& vec : fm3) {
            std::vector<int> copy = vec;
            copy.push_back(3);
            f.push_back(copy);
        }

        // for each element in f(i-2), append 2
        for (const auto& vec : fm2) {
            std::vector<int> copy = vec;
            copy.push_back(2);
            f.push_back(copy);
        }

        std::swap(fm3, fm2);  // update f(i-3)
        std::swap(fm2, fm1);  // update f(i-2)
        std::swap(fm1, f);    // update f(i-1)
    }

    return fm1;
}

/**
 * Compares two rows and returns true if there is a crack between the two rows.
 */
bool has_crack(const std::vector<int>& a, const std::vector<int>& b)
{
    int sum_a = 0;
    int sum_b = 0;

    int idx_a = 0;
    int idx_b = 0;

    while (idx_a < a.size() && idx_b < b.size()) {
        if (sum_a == sum_b && sum_a != 0) {
            return true;
        } else if (sum_a < sum_b) {
            sum_a += a.at(idx_a);
            ++idx_a;
        } else {
            sum_b += b.at(idx_b);
            ++idx_b;
        }
    }
    return false;
}

long p215()
{
    const int width = 32;
    const int height = 10;

    // get all rows of bricks
    const std::vector<std::vector<int>> rows = get_brick_rows(width);
    const int num_rows = rows.size();

    // populate transition matrix
    MatrixXl matrix = MatrixXl::Zero(num_rows, num_rows);
    for (int i = 0; i < num_rows; ++i) {
        for (int j = i + 1; j < num_rows; ++j) {  // diagonal is always 0
            if (!has_crack(rows.at(i), rows.at(j))) {
                matrix(i, j) = 1;
                matrix(j, i) = 1;  // matrix is symmetric
            }
        }
    }

    // compute the number of ways to fill the wall
    VectorXl state = VectorXl::Ones(num_rows);
    for (int i = 0; i < height - 1; ++i) {
        state = matrix * state;
    }

    return state.sum();
}

int main()
{
    printf("%ld\n", p215());
}
