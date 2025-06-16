#include <Eigen/Dense>

/*

One can prove the following simpler recurrence relations:

    A(m, n) = 3 A(m-1, n) + A(m-2, n)
    A(m, n) = A(m, n-1) + 3 A(m, n-2)

We can compute A(m, n) by computing A(m, 0) and A(m, 1) using the first recurrence relation, and then computing A(m, n)
using the second recurrence relation. The only difficulty then comes from computing A(m, n) for arbitrarily large
values, which can be cone by re-casting the recurrence relations as a matrix multiplication, e.g. for the first one,

    {{3, 1},     {A(m-1, n),
     {1, 0}}  *   A(m-2, n)}

and then using "exponentiation by squaring" to quickly compute high powers of these matrices.

ANSWER 969134784

*/

using Matrix2l = Eigen::Matrix<long, 2, 2>;
using Vec2l = Eigen::Matrix<long, 2, 1>;

constexpr int NUM_FIB = 50;

constexpr long MOD = 1123581313;

/**
 * Get Fibonacci numbers up to f{NUM_FIBS}, where f0 = 0 and f1 = 1.
 */
std::array<long, NUM_FIB + 1> get_fibs()
{
    std::array<long, NUM_FIB + 1> fibs;
    fibs[0] = 0;
    fibs[1] = 1;
    for (int i = 2; i <= NUM_FIB; ++i) {
        fibs[i] = fibs[i - 1] + fibs[i - 2];
    }
    return fibs;
}

/**
 * Takes modulo of integer-valued matrix. Modifies `a` in-place.
 */
void take_mod(Matrix2l& a, long m)
{
    a(0, 0) %= m;
    a(1, 0) %= m;
    a(0, 1) %= m;
    a(1, 1) %= m;
}

/**
 * Computes the modular power of an integer-valued matrix, a^b mod m.
 */
Matrix2l modular_power(const Matrix2l& a, long b, long m)
{
    assert(b >= 0);

    Matrix2l x = a;
    Matrix2l result{{1, 0}, {0, 1}};
    while (b > 0) {
        if (b & 1) {  // if (b % 2) == 1
            result = result * x;
            take_mod(result, m);
        }
        x = x * x;
        take_mod(x, m);
        b >>= 1;
    }
    return result;
}

long p940()
{
    const auto fibs = get_fibs();

    // transition matrix for increasing m
    const Matrix2l transition_m{{3, 1}, {1, 0}};
    // transition matrix for increasing n
    const Matrix2l transition_n{{1, 3}, {1, 0}};

    constexpr long A00 = 0;
    constexpr long A10 = 1;
    constexpr long A01 = 1;
    constexpr long A11 = 2;

    long sum = 0;
    for (int i = 2; i <= NUM_FIB; ++i) {
        const long fi = fibs[i];

        // compute A(fi, 0) and A(fi, 1)
        long Afi0, Afi1;
        {
            const Matrix2l transition = modular_power(transition_m, fi - 1, MOD);

            const Vec2l v0{A10, A00};
            Afi0 = (transition * v0)[0] % MOD;

            const Vec2l v1{A11, A01};
            Afi1 = (transition * v1)[0] % MOD;
        }

        for (int j = 2; j <= NUM_FIB; ++j) {
            const long fj = fibs[j];

            // compute A(fi, fj)
            long Afifj;
            {
                const Matrix2l transition = modular_power(transition_n, fj - 1, MOD);

                const Vec2l v{Afi1, Afi0};
                Afifj = (transition * v)[0] % MOD;
            }

            sum = (sum + Afifj) % MOD;
        }
    }

    return sum;
}


int main()
{
    printf("%ld\n", p940());
}
