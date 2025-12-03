#include <mf/mathfuncs.hpp>

/*

Since a+1, b+1, c+1 form a geometric sequence, we can note that

    (b+1)^2 = (a+1)(c+1)

This means that if we prime factorize (b+1)^2, we can iterate over its divisors to create candidate a+1 and c+1 pairs.
What remains is to check that a and c are primes.

ANSWER 100315739184392

*/

constexpr int LIMIT = 1e8;

/**
 * Given prime factorization, produce divisors less than `n`.
 *
 * Taken from Problem 955.
 */
std::vector<long> divisors_less_than_n(const std::vector<mf::PrimePower>& prime_factors, long n)
{
    std::vector<long> divisors = {1};
    for (const auto& prime_factor : prime_factors) {
        // first, generate all prime powers
        std::vector<long> powers;
        powers.reserve(prime_factor.exp);
        long power = 1;
        for (int i = 0; i < prime_factor.exp; ++i) {
            power *= prime_factor.base;
            if (power >= n) {
                break;
            }
            powers.push_back(power);
        }
        // multiply prime powers against all divisors
        std::vector<long> new_divisors;
        new_divisors.reserve(powers.size() * divisors.size());
        for (auto divisor : divisors) {
            for (auto power : powers) {
                const long new_divisor = power * divisor;
                if (new_divisor >= n) {
                    break;
                }
                new_divisors.push_back(new_divisor);
            }
        }
        divisors.insert(divisors.end(), new_divisors.begin(), new_divisors.end());
    }
    return divisors;
}

long p518()
{
    // collect list of primes
    const auto sieve = mf::prime_factor_sieve(LIMIT);

    auto is_prime = [&](int p) -> bool { return sieve[p] == p; };

    std::vector<int> primes;
    for (int p = 2; p < LIMIT; ++p) {
        if (is_prime(p)) {
            primes.push_back(p);
        }
    }

    long sum = 0;

    for (long b : primes) {
        // prime factorize (b + 1)^2
        auto pf = mf::prime_factorize(b + 1, sieve);
        for (auto& factor : pf) {
            factor.exp *= 2;
        }

        // get divisors of (b + 1)^2 less than b
        const auto divs = divisors_less_than_n(pf, b);

        for (long div : divs) {
            const long a = div - 1;
            const long c = ((b + 1) * (b + 1)) / div - 1;
            if (a > 1 && c < LIMIT && is_prime(a) && is_prime(c)) {
                sum += a + b + c;
            }
        }
    }
    return sum;
}

int main()
{
    printf("%ld\n", p518());
}
