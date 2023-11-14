#pragma once

#include "common.h"

#include <cmath>

/**
 * Tests equality between two floats, up to specified numerical tolerance.
 */
bool is_equal(double a, double b, double eps = 1e-15)
{
    return abs(a - b) < eps;
}
