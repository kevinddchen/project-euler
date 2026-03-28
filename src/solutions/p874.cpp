#include "mf/mathfuncs.hpp"

#include <Eigen/Dense>

#include <numeric>
#include <optional>
#include <span>
#include <vector>

/*

We can solve the equivalent problem: find nonnegative integers m0, m1, ..., m{k-1} such that:
 - sum of all m_a = n
 - sum of all a * m_a = multiple of k
 - maximize sum of all p_a * m_a, where p_a is the ath prime
Basically, m_a equals the multiplicity of `a` in the original problem.

Note that since we want the largest multiple of k in the second equation, it must equal the largest multiple of k no
greater than `n * (k-1)`.

In this form, the problem takes on the form of a linear optimization problem. I already wrote a C program to solve this
exact kind of problem, so the only difficulty was porting it to C++.

ANSWER 4992775389

*/

using ArrayXXl = Eigen::Array<long, Eigen::Dynamic, Eigen::Dynamic>;
using ColXl = Eigen::Array<long, Eigen::Dynamic, 1>;

/**
 * Compute first `size` primes.
 */
std::vector<long> get_primes(size_t size)
{
    std::vector<long> primes = {2};
    primes.reserve(size);
    long p = 1;
    while (primes.size() < size) {
        p += 2;
        if (mf::is_prime(p))
            primes.push_back(p);
    }
    return primes;
}

/**
 * Return largest multiple of k no greater than `n * (k-1)`.
 */
long get_multiple(long k, long n)
{
    long mod = n / k;
    if (n % k != 0)
        mod++;
    return (n - mod) * k;
}

// ============================================================================
// Code for linear program solver adapted from original C code here:
// https://github.com/kevinddchen/aoc_c/blob/5c82596c53316481a6e3ecdc95ae807e58f98a0c/src/apps/day10.c
// ============================================================================

/**
 * Normalize row by dividing by the greatest common divisor.
 */
void normalize_row(ArrayXXl& array, long row)
{
    long divisor = 0;
    for (long val : array.row(row)) {
        divisor = std::gcd(val, divisor);
        if (divisor == 1)
            return;
    }

    if (divisor == 0)  // entire row is 0
        return;

    array.row(row) /= divisor;
}

/**
 * Initialize tableau of the linear program.
 *
 * Example for k=4, n=10:
 *
 *  1  2  3  5  7  0  <-- objective function row
 *  0  1  1  1  1  10 <-- sum ma = n constraint
 *  0  0  1  2  3  28 <-- sum a * ma = multiple of k constraint
 *     ^  ^  ^  ^  ^
 *     m0 m1 m2 m3 RHS
 *
 * @param k
 * @param n
 * @param primes First k primes.
 */
ArrayXXl create_tableau(long k, long n, std::span<const long> primes)
{
    assert(static_cast<long>(primes.size()) >= k);

    ArrayXXl tableau(3, k + 2);

    // row 0
    tableau(0, 0) = 1;
    for (long i = 0; i < k; i++)
        // NOTE: use positive values to solve the negative problem, since our implementation finds the minimum
        tableau(0, i + 1) = primes[i];
    tableau(0, k + 1) = 0;

    // row 1
    tableau(1, 0) = 0;
    for (long i = 0; i < k; i++)
        tableau(1, i + 1) = 1;
    tableau(1, k + 1) = n;

    // row 2
    tableau(2, 0) = 0;
    for (long i = 0; i < k; i++)
        tableau(2, i + 1) = i;
    tableau(2, k + 1) = get_multiple(k, n);

    return tableau;
}

/**
 * Create auxiliary tableau, which is used to put `tableau` into canonical form.
 *
 *  1  0  0  0  0  0  -1 -1 0  <-- auxiliary objective function row
 *  0  1  2  3  5  7  0  0  0
 *  0  0  1  1  1  1  1  0  10
 *  0  0  0  1  2  3  0  1  28
 *                    ^  ^
 *                    auxiliary variables
 */
ArrayXXl create_auxiliary_tableau(const ArrayXXl& tableau)
{
    const long num_aux_vars = tableau.rows() - 1;

    const long rows = tableau.rows() + 1;
    const long cols = tableau.cols() + num_aux_vars + 1;
    ArrayXXl aux_tableau(rows, cols);

    aux_tableau.setZero();
    aux_tableau(0, 0) = 1;

    // copy tableau
    aux_tableau.block(1, 1, tableau.rows(), tableau.cols() - 1) = tableau.leftCols(tableau.cols() - 1);
    aux_tableau.block(1, cols - 1, tableau.rows(), 1) = tableau.rightCols(1);

    // init auxiliary objective function row: Z' - y0 - y1 - ... - y{k-1} = 0 (want to minimize Z' to 0)
    for (long i = 0; i < num_aux_vars; i++)
        aux_tableau(0, i + tableau.cols()) = -1;

    // init constraints for auxiliary variables, which is diagonal matrix
    for (long i = 0; i < num_aux_vars; i++)
        aux_tableau(i + 2, i + tableau.cols()) = 1;

    // add all rows to auxiliary objective function
    for (long i = 0; i < num_aux_vars; i++)
        aux_tableau.row(0) += aux_tableau.row(i + 2);
    normalize_row(aux_tableau, 0);

    return aux_tableau;
}

/**
 * Copy original tableau from `aux_tableau`.
 */
ArrayXXl extract_original_tableau(const ArrayXXl& aux_tableau)
{
    const long num_aux_vars = aux_tableau.rows() - 2;

    const long rows = aux_tableau.rows() - 1;
    const long cols = aux_tableau.cols() - num_aux_vars - 1;
    ArrayXXl tableau(rows, cols);

    // copy from aux_tableau
    tableau.leftCols(cols - 1) = aux_tableau.block(1, 1, rows, cols - 1);
    tableau.rightCols(1) = aux_tableau.block(1, aux_tableau.cols() - 1, rows, 1);

    for (long i = 0; i < tableau.rows(); i++)
        normalize_row(tableau, i);

    return tableau;
}

/**
 * Return a pivot column that will reduce the objective function. Otherwise, returns std::nullopt.
 * @param tableau
 * @param auxiliary True if this is the auxiliary tableau.
 */
std::optional<long> find_pivot_column(const ArrayXXl& tableau, bool auxiliary)
{
    // if auxiliary, first two columns are for normalization. otherwise, first column is for normalization.
    const long start_col = auxiliary ? 2 : 1;
    // if auxiliary, do not pick pivot from auxiliary variables
    const long end_col = auxiliary ? tableau.cols() - (tableau.rows() - 2) - 2 : tableau.cols() - 2;
    // if auxiliary, first two rows are objective rows. otherwise, first row is objective row.
    const long start_row = auxiliary ? 2 : 1;
    const long end_row = tableau.rows() - 1;

    // Devex algorithm: pick column with greatest "steepness"
    std::optional<long> pivot_col = {};
    double max_steepness = {};

    for (long col = start_col; col <= end_col; col++) {
        const long rise = tableau(0, col);
        // "rise" must be positive to reduce objective function
        if (rise <= 0)
            continue;

        // compute "tread" of the column
        long tread_squared = 0;
        for (long row = start_row; row <= end_row; row++) {
            const long val = tableau(row, col);
            tread_squared += val * val;
        }

        // "steepness" is rise over tread
        const double steepness = rise / std::sqrt(tread_squared);
        if (!pivot_col.has_value() || steepness > max_steepness) {
            pivot_col = col;
            max_steepness = steepness;
        }
    }
    return pivot_col;
}

/**
 * Given pivot column, return a pivot row that ensures all m0, m1, ..., m{k-1} variables remain nonnegative after pivot.
 * @param tableau
 * @param pivot_col Pivot column.
 * @param auxiliary True if this is the auxiliary tableau.
 */
long find_pivot_row(const ArrayXXl& tableau, long pivot_col, bool auxiliary)
{
    // if auxiliary, first two rows are objective rows. otherwise, first row is objective row.
    const long start_row = auxiliary ? 2 : 1;
    const long end_row = tableau.rows() - 1;

    // pick the row with minimum b_r / a_{rc} ratio.
    std::optional<long> pivot_row = {};
    double min_ratio = {};

    for (long row = start_row; row <= end_row; row++) {
        const long a = tableau(row, pivot_col);
        const long b = tableau(row, tableau.cols() - 1);

        // pivot element must be positive
        if (a <= 0)
            continue;
        assert(b >= 0);

        const double ratio = b / static_cast<double>(a);
        if (!pivot_row.has_value() || ratio < min_ratio) {
            pivot_row = row;
            min_ratio = ratio;
        }
    }
    return pivot_row.value();
}

/**
 * Perform pivot operation.
 * @param tableau
 * @param pivot_row Pivot row.
 * @param pivot_col Pivot column.
 */
void pivot(ArrayXXl& tableau, long pivot_row, long pivot_col)
{
    const long pivot_el = tableau(pivot_row, pivot_col);

    for (long row = 0; row < tableau.rows(); row++) {
        // skip pivot row
        if (row == pivot_row)
            continue;

        const long val = tableau(row, pivot_col);
        if (val == 0)
            continue;

        // multiply row to multiple of `pivot_el`
        tableau.row(row) *= pivot_el;

        // reduce row by subtracting multiple of pivot row
        tableau.row(row) -= val * tableau.row(pivot_row);

        // normalize row
        normalize_row(tableau, row);
    }
}

/**
 * Repeatedly perform pivot operations until objective function cannot be minimized further.
 * @param tableau
 * @param auxiliary True if this is the auxiliary tableau.
 */
void loop_pivot(ArrayXXl& tableau, bool auxiliary)
{
    std::optional<long> pivot_col = {};
    while (pivot_col = find_pivot_column(tableau, auxiliary), pivot_col.has_value()) {
        const long pivot_row = find_pivot_row(tableau, pivot_col.value(), auxiliary);
        pivot(tableau, pivot_row, pivot_col.value());
    }
}

/**
 * Checks that all `values[i]` are multiples of `coeffs[i]`.
 */
bool all_multiples_of_coeffs(const ColXl& values, const ColXl& coeffs)
{
    assert(values.rows() == coeffs.rows());
    for (long i = 0; i < values.rows(); i++) {
        if (coeffs[i] == 0) {
            if (values[i] != 0)
                return false;
        } else if (values[i] % coeffs[i] != 0) {
            return false;
        }
    }
    return true;
}

/**
 * Return the minimal integral score for the solved linear program.
 * @param tableau
 */
long min_integral_score(const ArrayXXl& tableau)
{
    // At this point, we have a reduced system of equations for variables Z, m0, m1, ..., m{k-1} and the last column
    // being the equation right-hand-side values.

    // We define "free variables" as ma left undetermined by the system of equations. These necessarily correspond to
    // columns that are not fully reduced and have more than 1 non-zero element. For each "non-free variable", we note
    // the coefficient multiplying it.

    std::vector<long> free_col_idxs;                        // i.e. columns corresponding to "free variables"
    ColXl nonfree_coeffs = ColXl::Zero(tableau.rows(), 1);  // coefficients in columns for "non-free variables"

    for (long col = 0; col <= tableau.cols() - 2; col++) {
        long nonzero_count = 0;
        std::optional<long> nonfree_row = {};
        for (long row = 0; row < tableau.rows(); row++) {
            if (tableau(row, col) != 0) {
                nonzero_count++;
                nonfree_row = row;
            }
        }
        if (nonzero_count > 1)
            free_col_idxs.push_back(col);
        else
            nonfree_coeffs(nonfree_row.value()) = tableau(nonfree_row.value(), col);
    }

    assert(nonfree_coeffs(0) != 0);  // coeff corresponding to Z must be non-zero

    // For an integral solution, the RHS values must be divisible by the coefficients in `nonfree_coeffs`. We have the
    // freedom of subtracting multiples of the columns `free_cols` corresponding to the "free variables". We do a very
    // inefficient brute-force search, in the sense that we may traverse the same node of the graph multiple times. But
    // at least this is easier to implement.

    // copy free-variable columns to `free_cols`
    std::vector<ColXl> free_cols;
    for (auto col_idx : free_col_idxs)
        free_cols.push_back(tableau.col(col_idx));

    // tracks our search. initialize with column of RHS values
    std::vector<ColXl> value_cols;
    value_cols.push_back(tableau.col(tableau.cols() - 1));

    // Brute-force search!

    long best_z = {};  // best objective function value
    bool best_z_set = false;
    for (size_t i = 0; i < value_cols.size(); i++) {
        const auto value_col = value_cols[i];  // copy, since we are changing the vector `value_cols`

        // exit if no chance of strictly better Z
        if (best_z_set && best_z * nonfree_coeffs[0] <= value_col[0])
            continue;

        // exit if any xi are negative
        if ((value_col.bottomRows(value_col.rows() - 1) < 0).any())
            continue;

        if (all_multiples_of_coeffs(value_col, nonfree_coeffs)) {
            const long z = value_col[0] / nonfree_coeffs[0];
            if (!best_z_set || z < best_z) {
                best_z = z;
                best_z_set = true;
            }
        }

        // we subtract each col in `free_cols` from `value_col`, and append to the vector
        for (const auto& free_col : free_cols) {
            value_cols.push_back(value_col - free_col);
        }
    }

    assert(best_z_set);
    return best_z;
}

// ============================================================================

long p874()
{
    constexpr long k = 7000;

    const auto primes = get_primes(k + 1);
    const long n = primes[k];

    auto tableau = create_tableau(k, n, primes);

    // to put `tableau` into canonical form, we first solve the auxiliary problem
    auto aux_tableau = create_auxiliary_tableau(tableau);
    loop_pivot(aux_tableau, true);
    assert(aux_tableau(0, aux_tableau.cols() - 1) == 0);  // check auxiliary problem is solved

    // now that the original problem is in canonical form, it can be solved
    tableau = extract_original_tableau(aux_tableau);
    loop_pivot(tableau, false);

    // since we solved the negative problem, we negate to get the actual answer
    return -min_integral_score(tableau);
}

int main()
{
    printf("%ld\n", p874());
}
