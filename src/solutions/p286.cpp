#include "mf/mathfuncs.hpp"

#include <array>

/*

Given a value of q, we can compute the generating function for the scores:

    g(x) = [1/q + (1-1/q)x][2/q + (1-2/q)x] ... [50/q + (1-50/q)x]

The probability is then the coefficient of x^20. We can then use binary search
to look for the value of q that leads to the desired probability.

ANSWER 52.6494571953

*/

constexpr int DEGREE = 50;

/**
 * Multiply the polynomial by the binomial a + bx. Operation is in-place.
 */
void multiply_binomial(std::array<double, DEGREE + 1>& polyn, double a, double b)
{
    for (int d = DEGREE; d > 0; --d) {
        polyn[d] = a * polyn[d] + b * polyn[d - 1];
    }
    polyn[0] = a * polyn[0];
}

/**
 * Generate the coefficients of the generating function for a given q.
 */
std::array<double, DEGREE + 1> get_generating_function(double q)
{
    assert(q > 50);

    // initialize polynomial = 1
    std::array<double, DEGREE + 1> polyn;
    polyn.fill(0);
    polyn[0] = 1;

    // multiply binomials
    for (int i = 1; i <= DEGREE; ++i) {
        const double a = i / q;
        const double b = 1 - a;
        multiply_binomial(polyn, a, b);
    }

    return polyn;
}

/**
 * Get probability of 20 points.
 */
double get_probability(double q)
{
    const auto func = get_generating_function(q);
    return func[20];
}

double p286()
{
    constexpr double target = 0.02;
    constexpr double tol = 1e-10;

    // use binary search to find q such that prob(q) = 0.02
    // prob(q=51) = 0.031619
    // prob(q=60) = 0.002205
    // thus probability decreases with q

    double q_left = 51;
    double q_right = 60;

    while (q_right - q_left > tol) {
        const double q = (q_right + q_left) / 2;
        const double prob = get_probability(q);

        if (prob >= target) {
            q_left = q;
        } else {
            q_right = q;
        }
    }

    return (q_right + q_left) / 2;
}

int main()
{
    printf("%.10f\n", mf::round(p286(), 10));
}
