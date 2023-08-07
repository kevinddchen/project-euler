#include "common.h"
#include "mathfuncs.h"

/*

https://en.wikipedia.org/wiki/Cubic_equation#Cardano's_formula

We use Cardano's formula to solve the cubic equation:

    t^3 + 3pt - 2q = 0.

If p, q are real and Delta = q^2 + p^3 > 0, then the equation has only one real
root given by t = u_1^(1/3) + u_2^(1/3) where

    u_1, u_2 = q +/- sqrt(Delta).

Moreover, suppose the real root equals 1. This is only possible if 3p + 1 = 2q.
Then we have a Cardano Triplet for a = q and b^2 * c = Delta. In fact, we can
also write Delta = ((p+1)/2)^2 * (4p + 1), which avoids integer overflow and is
easier to factorize. So we just have to iterate through all odd values of p =
1, 3, 5, ..., calculate a, and then iterate through all values of b, c given by
the square factors of Delta.

What is the upper bound on p? First, note that the sum b + c subject to the
constraint b^2 * c = Delta is minimized when b = (2 Delta)^(1/3) and c =
2^(-2/3) Delta^(1/3). This fact can be proven using calculus. Then, if we
further note that Delta > p^3 and q > (3/2)p, we have the inequality,

    a + b + c > (3/2 + 2^(1/3) + 2^(-2/3)) p ~= 3.39 p.

This means that the largest value of p we will encounter is less than N / 3.39.
Thus the largest number we will need to prime factorize is (4p + 1) ~= 4N /
3.39 ~= 1.18N. This is important only because we use a prime sieve to speed up
factorization.

ANSWER 18946051

*/


long p251()
{
    const long limit = 110'000'000;

    const auto factor_sieve = mf::prime_factor_sieve(1.2 * limit);  // (see above for this bound)

    long count = 1;                               // for p = 1
    for (long p = 3; p * 3.38 < limit; p += 2) {  // (see above for this bound)

        // first, get prime factorization of Delta
        std::vector<mf::PrimePower> prime_powers;
        {
            const long s = (p + 1) / 2;
            std::vector<mf::PrimePower> s_prime_powers = mf::prime_factorize(s, factor_sieve.get());
            // double all exponents
            for (auto& s_fact : s_prime_powers) {
                s_fact.exp *= 2;
            }

            const long t = 4 * p + 1;
            const std::vector<mf::PrimePower> t_prime_powers = mf::prime_factorize(t, factor_sieve.get());

            prime_powers = mf::merge_prime_factors(s_prime_powers, t_prime_powers);
        }

        // second, get all b < N such that b^2 divides Delta
        std::vector<long> bs = {1};
        for (const auto& prime_power : prime_powers) {
            if (prime_power.exp == 1) {
                continue;
            }
            long factor = prime_power.base;
            std::vector<long> new_bs;
            for (int exp = 2; exp <= prime_power.exp; exp += 2) {
                if (factor >= limit) {
                    break;
                }
                for (const auto& b : bs) {
                    const long new_b = b * factor;
                    if (new_b < limit) {
                        new_bs.push_back(new_b);
                    }
                }
                factor *= prime_power.base;
            }
            bs.insert(bs.end(), new_bs.begin(), new_bs.end());
        }

        // third, for each b: compute c, and check that c < N
        std::vector<std::pair<long, long>> bcs;
        {
            const double log_delta = std::log((p + 1) / 2) + std::log(4 * p + 1);
            const double log_limit = std::log(limit);

            for (const long b : bs) {
                // check if c is safe to compute
                const double log_b = std::log(b);
                const double log_c = log_delta - 2 * log_b;
                if (log_c > log_limit) {
                    continue;
                }

                // compute c
                long b_copy = b;
                long c = 1;
                for (const auto& prime_power : prime_powers) {
                    const long prime = prime_power.base;
                    int exp = prime_power.exp;
                    while (exp > 0) {
                        if (b_copy % prime == 0) {
                            b_copy /= prime;
                            exp -= 2;
                        } else {
                            c *= prime;
                            exp--;
                        }
                    }
                }

                bcs.push_back({b, c});
            }
        }

        // fourth, for each b, c: check if a + b + c <= N
        for (const auto& [b, c] : bcs) {
            const long a = (3 * p + 1) / 2;
            if (a + b + c <= limit) {
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
