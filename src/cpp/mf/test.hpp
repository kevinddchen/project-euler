#pragma once

#include <cmath>


namespace mf::test
{

/**
 * Tests equality between two floats, up to specified numerical tolerance.
 */
inline bool is_equal(double a, double b, double eps = 1e-15)
{
    return std::abs(a - b) < eps;
}

}  // namespace mf::test
