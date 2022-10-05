#include "common.h"
#include "mathfuncs.h"

#include <array>

#include <cmath>

/*

We can use Snell's law to find the minimum time. Using a geometric optics
interpretation, given an initial "angle of incidence", we can compute the
"angle of refraction" through each region. Since time is automatically
minimized, all we have to do is ensure that we reach the desired final
location.

Once we find this "angle of incidence", we can directly compute the time of
travel.

ANSWER 13.1265108586

*/

// number of regions in the marsh
constexpr int N = 5;
// speed outside the marsh, in leagues per day
constexpr double V = 10.0;
// total straight distance, in leagues
constexpr double D = 100.0;
// total distance perpenticular to the marsh, in leagues
constexpr double PERP_D = D / M_SQRT2;
// thickness of each marsh region, in leagues
constexpr double T = 10.0;
// distance to travel perpendicular to the marsh while outside the marsh, in leagues
constexpr double PERP_NONMARSH_D = PERP_D - N * T;

/**
 * Given the angle of incidence entering the marsh, calculate the angles of
 * refraction through each region.
 */
std::array<double, N> get_angles_of_refraction(double angle_of_incidence)
{
    const double s_inc = sin(angle_of_incidence);

    std::array<double, N> angles;
    for (int i = 0; i < N; i++) {
        // speed of ith region is (10 - i) for i = 1, 2, 3, 4, 5
        const double v_i = V - static_cast<double>(i + 1);
        angles[i] = asin(s_inc * v_i / V);  // Snell's law
    }
    return angles;
}

/**
 * Given the angle of incidence entering the marsh, calculate the total
 * distance travelled parallel to the marsh. For a valid route, this must equal
 * PERP_D.
 */
double parallel_distance(double angle_of_incidence)
{
    const std::array<double, N> angles_of_refraction = get_angles_of_refraction(angle_of_incidence);

    double par_dist = PERP_NONMARSH_D * tan(angle_of_incidence);
    for (auto angle : angles_of_refraction) {
        par_dist += T * tan(angle);
    }
    return par_dist;
}

/**
 * `parallel_distance` is a monotone increasing function where 0 -> 0 and
 * pi/2 -> inf. We use binary search to find an input to this function that
 * equals `target`. More precisely, we find a window [min, max] of the domain
 * that contains `target` in the range, where the window is 2^(-n_bisects) the
 * size of the original domain.
 */
void binary_search(double& min, double& max, double target, int n_bisects)
{
    assert(target > 0);
    for (int i = 0; i < n_bisects; i++) {
        const double mid = (min + max) / 2.0;
        const double val = parallel_distance(mid);
        if (val == target) {
            min = mid;
            max = mid;
            break;
        } else if (val < target) {
            min = mid;
        } else {
            max = mid;
        }
    }
}

/**
 * Given the angle of incidence, compute the total time of the route.
 */
double total_time(double angle_of_incidence)
{
    const std::array<double, N> angles_of_refraction = get_angles_of_refraction(angle_of_incidence);

    // distance travelled outside the marsh
    const double non_marshdist = PERP_NONMARSH_D / cos(angle_of_incidence);
    double time = non_marshdist / V;
    for (int i = 0; i < N; i++) {
        const double dist = T / cos(angles_of_refraction[i]);
        const double v_i = V - static_cast<double>(i + 1);
        time += dist / v_i;
    }
    return time;
}

double p607()
{
    // First, find the input angle that makes `parallel_dist == PERP_D`.
    double min = 0.0;
    double max = M_PI_2;
    binary_search(min, max, PERP_D, 40);  // 2^(-40) is approximately 1e-12, which should be enough precision
    const double angle_of_incidence = (min + max) / 2.0;

    // Sanity check
    assert(abs(parallel_distance(angle_of_incidence) - PERP_D) < 1e-10);

    return total_time(angle_of_incidence);
}

int main()
{
    TIMED(printf("%.10f\n", mf::round(p607(), 10)));
}
