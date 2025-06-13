#include <Eigen/Dense>

/*

Given a state (R, B), we can work out that after repeated trials, we will eventually transition to

    state (R-2, B) with probability R(R-1) / [R(R-1) + 2RB]
    state (R, B-1) with probaility 2RB / [R(R-1) + 2RB]

This then becomes a dynamic programming question, with the boundary conditions P(0, B) = 1 and P(R, 0) = 0. We create an
array containing values of P(R, B), and work our way outwards from the P(1, 1) corner.

ANSWER 0.2928967987

*/


// Sentinel value marking an uncomputed probability.
constexpr double MISSING_VALUE = -1.0;


/**
 * Get previously computed P(red, black).
 */
double get_prob(int red, int black, const Eigen::ArrayXXd& P)
{
    if (black == 0) {
        return 0;
    } else if (red == 0) {
        return 1;
    } else if (red < 0 || black < 0) {
        assert(red == -1);
        // undefined, so return 0
        return 0;
    }
    const double p = P(red, black);
    assert(p != MISSING_VALUE);
    return p;
}


double p938()
{
    constexpr int MAX_R = 24690;
    constexpr int MAX_B = 12345;

    // array to store probabilities
    Eigen::ArrayXXd P(MAX_R + 1, MAX_B + 1);
    P.fill(MISSING_VALUE);

    for (int red = 1; red <= MAX_R; ++red) {
        for (int black = 1; black <= MAX_B; ++black) {
            const double denom = red * (red - 1) + 2 * red * black;
            const double two_red_transition = red * (red - 1) / denom;
            const double two_red_prob = get_prob(red - 2, black, P);
            const double one_each_transition = 2 * red * black / denom;
            const double one_each_prob = get_prob(red, black - 1, P);
            const double prob = two_red_transition * two_red_prob + one_each_transition * one_each_prob;
            P(red, black) = prob;
        }
    }

    return P(MAX_R, MAX_B);
}

int main()
{
    printf("%.10f\n", p938());
}
