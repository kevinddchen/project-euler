#include "common.h"
#include "mathfuncs.h"

#include <array>

/*

ANSWER

*/

using Matrix2l = std::array<std::array<long, 2>, 2>;

/**
 * Modular matrix multiplication.
 */
Matrix2l mod_mul(const Matrix2l& a, const Matrix2l& b, long m)
{
    Matrix2l result;
    result[0][0] = (mf::modular_product(a[0][0], b[0][0], m) + mf::modular_product(a[0][1], b[1][0], m)) % m;
    result[0][1] = (mf::modular_product(a[0][0], b[0][1], m) + mf::modular_product(a[0][1], b[1][1], m)) % m;
    result[1][0] = (mf::modular_product(a[1][0], b[0][0], m) + mf::modular_product(a[1][1], b[1][0], m)) % m;
    result[1][1] = (mf::modular_product(a[1][0], b[0][1], m) + mf::modular_product(a[1][1], b[1][1], m)) % m;
    return result;
}

/**
 * Compute the nth fibonacci number, mod m.
 */
long fib_mod(long n, long m)
{
    // Uses the fact that {{1, 1}, {1, 0}}^n = {{F_(n-1), F_n}, {F_n, F_(n-1)}}
    // Then use an analogous exponentiation by squaring algorithm
    Matrix2l base;
    base[0] = {1, 1};
    base[1] = {1, 0};
    Matrix2l result;
    result[0] = {1, 0};
    result[1] = {0, 1};

    while (n > 0) {
        if (n & 1) {  // if (n % 2) == 1
            result = mod_mul(result, base, m);
        }
        base = mod_mul(base, base, m);
        n >>= 1;
    }

    return result[0][1];
}

long p0()
{
    const long mod = 1234567891011;

    long x = static_cast<long>(1e14) - 1;

    int count = 0;
    while (count < 100) {
        x += 2;

        while (!mf::is_prime(x)) {
            x += 2;
        }

        long fib = fib_mod(x, mod);
        printf("F(%ld): %ld\n", x, fib, mod);
        ++count;
    }

    return 0;
}

int main()
{
    printf("%ld\n", p0());
}
