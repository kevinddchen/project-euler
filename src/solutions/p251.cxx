#include "common.h"
#include "mathfuncs.h"

#include <climits>

/*

https://en.wikipedia.org/wiki/Cubic_equation#Cardano's_formula

We use Cardano's formula to solve the cubic equation:

    t^3 + 3pt - 2q = 0.

If p, q are real and Delta = q^2 + p^3 > 0, then the equation has only one real
root given by t = u_1^(1/3) + u_2^(1/3) where

    u_1, u_2 = q +/- sqrt(Delta).

Moreover, suppose the real root equals 1. This is only possible if 3p + 1 = 2q.
Then we have a Cardano Triplet for a = q and b^2 * c = Delta. So we just have
to iterate through all values of q = 2 (mod 3), calculate p, and then iterate
through all values of b, c given by the square factors of Delta.

answer for N = 1'000: 149
answer for N = 1'000'000: 171128

ANSWER

*/

/**
 * Get all integers b < N such that b^2 divides Delta.
 */
std::vector<long> get_square_factors(long delta, long N)
{
    const std::vector<mf::PrimePower> prime_powers = mf::prime_factorize(delta);

    std::vector<long> bs = {1};
    for (const auto& prime_power : prime_powers) {
        if (prime_power.exp == 1) {
            continue;
        }
        long factor = prime_power.base;
        std::vector<long> new_bs;
        for (int exp = 2; exp <= prime_power.exp; exp += 2) {
            if (factor > N) {
                break;
            }
            for (const auto& b : bs) {
                const long new_b = b * factor;
                if (new_b < N) {
                    new_bs.push_back(new_b);
                }
            }
            factor *= prime_power.base;
        }
        bs.insert(bs.end(), new_bs.begin(), new_bs.end());
    }
    return bs;
}

long p251()
{
    // const long limit = 1000;
    const long limit = 1'000'000;
    const float two_to_four_thirds = std::pow(2.0, 1.0 / 3.0);

    long count = 0;
    for (long q = 2;; q += 3) {
        const long p = (2 * q - 1) / 3;

        if (q + p * two_to_four_thirds > limit) {
            break;
        }

        const long delta = q * q + p * p * p;
        assert(delta > 0);

        const std::vector<long> square_factors = get_square_factors(delta, limit);
        for (const long b : square_factors) {
            const long a = q;
            const long c = delta / b / b;
            if (a + b + c <= limit) {
                // printf("a=%ld, b=%ld, c=%ld, p=%ld, delta=%ld\n", a, b, c, p, delta);
                count++;
            }
        }
    }
    return count;
}

int main()
{
    TIMED(printf("%ld\n", p251()));
}
