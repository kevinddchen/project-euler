#include "common.h"

#include <Eigen/Dense>

/*

It is simple enough to count the step numbers with length up to 40 digits. We
define the state to be a vector of length 10, where the ith element represents
the count of step numbers that lead with the digit i. This state is initialized
to all ones. For 40 iterations, we sum the 1st-9th elements of the state (since
the 0th element is a leading zero) and then apply a transition matrix that
encodes the possible constructions of step numbers, e.g. a 0 must be followed
by a 1 and a 1 can be followed by a 0 or 2. This effectively counts the step
numbers with length 1, 2, 3, ..., 40.

The harder part is to count only pandigital step numbers. But we can use our
method above to count the step numbers using the digits 0-9, subtract off the
step numbers using the digits 0-8, subtract off the step numbers using the
digits 1-9, and add back the step numbers using the digits 1-7 (because they
were double subtracted). The only additional consideration is whether the
consecutive digits contain zero.

ANSWER 126461847755

*/

using MatrixXl = Eigen::Matrix<long, Eigen::Dynamic, Eigen::Dynamic>;
using VectorXl = Eigen::Matrix<long, Eigen::Dynamic, 1>;

/**
 * Get the transition matrix for `num_digits` consecutive digits. This is just
 * a band matrix with 0s on the diagonal and 1s just off the diagonal.
 */
MatrixXl get_transition_matrix(int num_digits)
{
    MatrixXl matrix = MatrixXl::Zero(num_digits, num_digits);

    for (int i = 1; i < num_digits; ++i) {
        matrix(i, i - 1) = 1;
        matrix(i - 1, i) = 1;
    }

    return matrix;
}

/**
 * Count step numbers up to `length` digits that are made of `num_digits`
 * consecutive digits. If the consecutive digits contain zero, leading zeros
 * are not counted.
 */
long count(int num_digits, int length, bool digits_contain_zero)
{
    assert(length >= 1);
    assert(num_digits >= 1);

    MatrixXl transition_matrix = get_transition_matrix(num_digits);
    VectorXl state = VectorXl::Ones(num_digits);
    long count = 0;

    for (int i = 0; i < length; ++i) {
        count += state.sum();

        // if the digits contain zero, we do not count leading zeros
        if (digits_contain_zero) {
            count -= state(0);
        }

        state = transition_matrix * state;
    }

    return count;
}

long p178()
{
    const int num_digits = 10;
    const int length = 40;
    return count(num_digits, length, true) - count(num_digits - 1, length, true) -
           count(num_digits - 1, length, false) + count(num_digits - 2, length, false);
}

int main()
{
    printf("%ld\n", p178());
}
