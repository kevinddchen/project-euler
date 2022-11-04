#pragma once

#include "common.h"
#include "containers.h"

#include <functional>

namespace mf::hash
{

size_t hash_combine(size_t lhs, size_t rhs)
{
    lhs ^= rhs + 0x9e3779b9 + (lhs << 6) + (lhs >> 2);
    return lhs;
}

}  // namespace mf::hash

// Since our fractions are always reduced, we can just hash the floating point value
template <>
struct std::hash<mf::Frac> {
    inline std::size_t operator()(const mf::Frac& frac) const { return std::hash<double>{}(frac.fp()); }
};
