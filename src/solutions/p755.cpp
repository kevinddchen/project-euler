#include "mf/mathfuncs.hpp"

#include <vector>

#include <cassert>

/*

Let the fibonacci numbers be denoted by f1 = 1, f2 = 2, f3 = 3, f4 = 5, f5 = 8, ...

We first define an auxiliary function f_i(n) as the number of ways to write n as the sum of distinct fibonacci numbers
<= fi, i.e. only using fibonacci numbers less than or equal to fi. Likewise, we can define the auxiliary sum s_i(n) in a
way similar to S(n), but sums over values of f_i(n) instead.

If we define boundary conditions,

1.  s_0(n) = 1 for all n
2.  s_i(n) = 0 for all i and all n < 0

then we can note the following recursion relation:

3.  s_i(n) = s_{i-1}(n) + s_{i-1}(n - fi)

This basically comes from the fact that the number of ways to write n as the sum of distinct fibonacci numbers <= fi is
equal to the sum of (a) the number of ways using distinct fibonacci numbers <= f{i-1}, plus (b) the number of ways to
write n - fi using distinct fibonacci numbers <= f{i-1}.

Then, we can also show two important facts:

4.  s_i(n) = 2^i if n >= f{i+2} - 2
5.  s_i(n) = S(n) if n < f{i+1}

Fact 4 comes from the fact that f1 + f2 + f3 + ... + fn = f_{n+2} - 2, and that there are 2^i possible sums involving
the numbers {f1, f2, f3, ..., fn}. Fact 5 comes from the fact that if n < f_{i+1}, then we can only write it as a sum of
fibonacci numbers < f_{i+1}, i.e. using fi and smaller.

Using these, we can compute S(n) recursively.

ANSWER 2877071595975576960

*/


/**
 * Compute the fibonacci numbers <= `limit`. The list starts with {0, 1, 2, ...}.
 */
std::vector<long> get_fibs(long limit)
{
    assert(limit >= 2);

    std::vector<long> fibs = {0, 1, 2};
    while (true) {
        const auto last_ptr = fibs.end() - 1;
        const long next_fib = *last_ptr + *(last_ptr - 1);
        if (next_fib > limit) {
            break;
        }
        fibs.push_back(next_fib);
    }
    return fibs;
}

/**
 * Compute s_i(n) using recursion.
 */
long compute_si(const std::vector<long>& fibs, int i, long n)
{
    // boundary conditions
    if (n < 0) {
        return 0;
    }
    if (i == 0) {
        return 1;
    }
    // check known value from fact 4
    if (i + 2 < static_cast<int>(fibs.size()) && n >= fibs[i + 2] - 2) {
        return mf::pow(2, i);
    }
    // otherwise use recursion
    const long fib_i = fibs[i];
    return compute_si(fibs, i - 1, n) + compute_si(fibs, i - 1, n - fib_i);
};

long p755()
{
    constexpr long TARGET = 1e13;

    // get fibonacci numbers up to `TARGET`
    const auto fibs = get_fibs(TARGET);
    const int num_fibs = fibs.size() - 1;

    return compute_si(fibs, num_fibs, TARGET);
}

int main()
{
    printf("%ld\n", p755());
}
