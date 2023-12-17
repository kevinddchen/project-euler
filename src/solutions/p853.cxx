#include "common.h"
#include "mathfuncs.h"

#include <numeric>

/*

By definition of the Pisano period, if pi(n) = 120 then Fib(120) = 0 (mod n)
and Fib(121) = 1 (mod n). This implies that n divides gcd(Fib(120), Fib(121)-1)
= Fib(60). Thus, we just need to compute the Pisano periods of all divisors of
Fib(60). This is aided by the following facts:

 -  pi(p^m)         = p^(m-1) * pi(m) ... technically still a conjecture
 -  pi(p^m * q^n)   = lcm( pi(p^m) , pi(q^n) )

ANSWER 44511058204

*/

/**
 * Computes the Pisano period of `n`.
 */
long pisano(long n)
{
    long a = 1;  // Fib i
    long b = 0;  // Fib i-1

    for (long i = 1;; ++i) {
        long c = (a + b) % n;
        b = a;
        a = c;
        if (a == 1 && b == 0) {
            return i;
        }
    }
}


long p853()
{
    const long target = 120;
    const long limit = 1'000'000'000;

    // prime factorize Fib(60)
    const auto factors = mf::prime_factorize(1'548'008'755'920);

    // compute the Pisano period for each prime factor
    std::vector<long> prime_pis;
    for (const auto& factor : factors) {
        prime_pis.push_back(pisano(factor.base));
    }

    // count divisors of Fib(60)
    long num_divisors = 1;
    for (const auto& factor : factors) {
        num_divisors *= (factor.exp + 1);
    }

    long sum = 0;

    // iterate over all divisors of Fib(60)
    // this is done by iterating over all combinations of prime factor exponents
    std::vector<long> exps(factors.size());
    // skip `div_idx = 0`, which is the divisor 1
    for (long div_idx = 1; div_idx <= num_divisors - 2; ++div_idx) {
        // populate `exps` with a unique combination
        {
            long i = div_idx;
            for (int j = 0; j < factors.size(); ++j) {
                const long max_exp = factors[j].exp + 1;
                exps[j] = i % max_exp;
                i /= max_exp;
            }
        }
        // compute the divisor represented by `exps`
        long n = 1;
        for (int j = 0; j < factors.size(); ++j) {
            n *= mf::pow(factors[j].base, exps[j]);
        }
        if (n >= limit) {
            continue;
        }
        // compute the Pisano period of `n`
        long pi = 1;
        for (int j = 0; j < factors.size(); ++j) {
            if (exps[j] > 0) {
                const long prime_pi = mf::pow(factors[j].base, exps[j] - 1) * prime_pis[j];
                pi = std::lcm(pi, prime_pi);
            }
        }

        if (pi == target) {
            sum += n;
        }
    }

    return sum;
}

int main()
{
    printf("%ld\n", p853());
}
