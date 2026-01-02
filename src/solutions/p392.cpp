#include "mf/mathfuncs.hpp"

#include <numbers>

/*

Consider the graph of the function y = 1 - sqrt(1 - (x-1)^2) for 0 <= x <= 1.
Any point (x, y) on this graph can be associated with an angle theta:

    x = 1 - cos(theta)          0 <= theta <= pi/2
    y = 1 - sin(theta)

We want to find theta_1, theta_2, ..., theta_N such that the following sum is
minimized:

    Area
    = 4 * sum_{i=1}^{N+1} (1 - y_i) * (x_i - x_{i-1})
    = 4 * sum_{i=1}^{N+1} sin(theta_i) * (cos(theta_{i-1}) - cos(theta_i))

where theta_0 = 0 and theta_{N+1} = pi/2. If we take the partial derivative
with respect to theta_i, we get:

    dArea / dtheta_i =  cos(theta_i) * cos(theta_{i-1})
                        - sin(theta_{i+1}) * sin(theta_i)
                        - cos(2 * theta_i)

Setting this to zero, we get an equation that gives theta_{i+1} in terms of
theta_{i-1} and theta_i. Therefore, starting with theta_0 = 0 and an initial
guess for theta_1, we can use the equations to compute values for theta_2,
theta_3, ..., theta_{N+1}. This should equal pi/2, so whether this is greater
than or less than pi/2 tells us whether our initial guess for theta_1 was too
low or too high. We can then use binary search to find the optimal value for
theta_1.

ANSWER 3.1486734435

*/

/**
 * Given theta_0 and theta_1, extrapolate out to theta_{N+1} which should
 * equal pi / 2. Returns true if theta_{N+1} > pi / 2, and false otherwise.
 */
double overshoots_target(double t0, double t1, int N)
{
    double tim1 = t0;
    double ti = t1;
    for (int i = 2; i <= N + 1; i++) {
        const double x = (std::cos(ti) * std::cos(tim1) - std::cos(2 * ti)) / std::sin(ti);
        if (x > 1) {  // overshoots target
            return true;
        }
        tim1 = std::asin(x);
        std::swap(ti, tim1);
    }
    return false;
}

/**
 * Given theta_0 and theta_1, compute the area under the curve.
 */
double get_area(double t0, double t1, int N)
{
    double tim1 = t0;
    double ti = t1;

    double xim1 = 1 - std::cos(tim1);

    // we use a slightly different sum here than given in the docstring above,
    // only because the extrapolated i = N+1 values are not very accurate.

    double area = 0;
    for (int i = 1; i <= N; i++) {
        const double xi = 1 - std::cos(ti);
        const double yi = 1 - std::sin(ti);
        area += yi * (xi - xim1);

        tim1 = std::asin((std::cos(ti) * std::cos(tim1) - std::cos(2 * ti)) / std::sin(ti));
        std::swap(ti, tim1);

        xim1 = xi;
    }
    return 4 * (1 - area);
}

double p392()
{
    const int N = 200;

    // determine min and max
    double max = std::numbers::pi / 2 / N;  // this will always be too small
    while (!overshoots_target(0, max, N)) {
        max *= 2;
    }
    double min = max / 2;

    // binary search
    while (max - min > 1e-15) {
        const double mid = (min + max) / 2;
        if (overshoots_target(0, mid, N)) {
            max = mid;
        } else {
            min = mid;
        }
    }

    const double area = get_area(0, min, N);
    return mf::round(area, 10);
}

int main()
{
    printf("%.10f\n", p392());
}
