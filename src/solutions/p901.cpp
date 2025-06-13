#include <algorithm>
#include <array>

#include <cassert>
#include <cmath>
#include <cstdio>

/*

Let the drill depths be d1, d2, d3, ... . One can show that the expected drilling time is

    T = d1 (1 - exp(-d1)) + (d1 + d2) * (exp(-d1) - exp(-d2)) + (d1 + d2 + d3) * (exp(-d2) - exp(-d3)) + ...
      = d1 + d2 * exp(-d1) + d3 * exp(-d2) + d4 * exp(-d3) + ...

The optimal strategy is the choice of d1, d2, d3, ... that minimizes this function. First, we can set the partial
derivatives with respect to d1, d2, d3, ... to zero to find the extrema of the function. This gives us,

    d2 = exp(d1)
    d3 = exp(d2 - d1)
    d4 = exp(d3 - d2)
    ...

Thus, T depends only on a single parameter, d1:

    T = d1 + 1 + exp(-d1) + exp(-d2) + exp(-d3) + ...

    d2 = exp(d1)
    d3 = exp(d2 - d1) = exp(exp(d1) - d1)
    ...
    dn = exp(d{n-1} - d{n-2})

A more convenient definition of T is

    T = t0 + t1 + t2 + t3 + t4 + ...

    t0 = d1
    t1 = 1
    tn = exp(-t{n-2} / t{n-1})

We can find the minimum of T w.r.t d1, the initial drill depth, via numerical search.

ANSWER 2.364497769

*/


/**
 * Given the initial drill depth, returns the expected total time for the optimal strategy.
 */
double expected_total_time(double initial_depth)
{
    constexpr double PRECISION = 1e-16;
    double a = initial_depth;
    double b = 1.0;

    double sum = a + b;
    while (true) {
        const double next = std::exp(-a / b);
        if (next < PRECISION) {
            break;
        }
        sum += next;
        a = b;
        b = next;
    }
    return sum;
}

double p901()
{
    double depth_left = 0;
    double depth_right = 2;

    // we search for the global minimum of the function `expected_total_time` over the interval [0, 2]. this is done by
    // a binary search of sorts: first compute the value of the function over several points. then find the minimum
    // value over these points. if the minimum is in the first half of the interval, shorten the interval to the first
    // two-thirds. if the minimum is in the second half of the interval, shorten the interval to the last two-thirds.
    // repeat. this makes several assumptions about the smoothness of the function, but it's good enough for us.

    // number of points to sample between depth_right and depth_left
    constexpr int SEARCH_SIZE = 18;
    // break when depth_right - depth_left is less than this.
    constexpr double MIN_DELTA_DEPTH = 1e-12;

    std::array<double, SEARCH_SIZE> times;

    while (depth_right - depth_left > MIN_DELTA_DEPTH) {
        // populate times
        const double delta_step = (depth_right - depth_left) / (SEARCH_SIZE - 1);
        for (int i = 0; i < SEARCH_SIZE; ++i) {
            const double depth = depth_left + i * delta_step;
            const double time = expected_total_time(depth);
            times[i] = time;
        }

        // find minimum
        const auto min_ptr = std::min_element(times.begin(), times.end());
        const int idx = std::distance(times.begin(), min_ptr);

        // reduce interval
        if (idx <= SEARCH_SIZE / 2) {
            depth_right = depth_left + 0.666667 * (depth_right - depth_left);
        } else {
            depth_left = depth_left + 0.333333 * (depth_right - depth_left);
        }
    }

    return *std::min_element(times.begin(), times.end());
}

int main()
{
    printf("%.9f\n", p901());
}
