#pragma once

#include <cstdio>


namespace mf::hash
{

inline size_t hash_combine(size_t lhs, size_t rhs)
{
    lhs ^= rhs + 0x9e3779b9 + (lhs << 6) + (lhs >> 2);
    return lhs;
}

}  // namespace mf::hash
