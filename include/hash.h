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

template <>
struct std::hash<mf::Frac> {
    inline std::size_t operator()(const mf::Frac& frac) const
    {
        return std::hash<float>{}(frac.numer / (float)frac.denom);
    }
};
