#include "common.h"
#include "mathfuncs.h"

#include <numeric>
#include <unordered_map>

/*

We first note some facts about repeating decimal expansions. These facts are
all from https://en.wikipedia.org/wiki/Repeating_decimal.

1.  The period of 1/p is the order of 10 mod p. The order will divide p - 1.
    Let us denote the period of 1/p as T(1/p) = T_p.

2.  The period of 1/p^k for k > 1 equals p^{k-1} * T_p EXCEPT when p is in the
    set {3, 487, 56598313}. In these cases, the period is p^{k-2} * T_p.

3.  The period of a composite number coprime to 10 is the LCM of the periods
    of its prime power factors.

4.  The period of a composite number whose prime factorization contains
    2^a * 5^b is the same as the period of the number without the 2^a * 5^b,
    but the repeating part of the decimal expansion starts after max(a, b)
    digits.

Using these facts and doing things efficiently by utilizing a prime sieve to
compute prime factors, we can compute the 10^7-th digit of all 1/n fractions.

ANSWER 44967734

*/

/**
 * Compute the multiplicative order of 10 modulo p. p must be prime not equal
 * to 2 or 5.
 *
 * Uses the fact that the order divides p - 1 to speed up the computation.
 */
int order_of_10(int p, const std::vector<int>& prime_factor_sieve)
{
    assert(prime_factor_sieve[p] == p);  // p must be prime
    assert(p != 2 && p != 5);

    const auto& facts = mf::prime_factorize(p - 1, prime_factor_sieve);

    // go through divisors of the totient and check for a smaller order
    int order = p - 1;
    for (const auto& fact : facts) {
        for (int i = 0; i < fact.exp; i++) {
            if (mf::modular_power(10, order / fact.base, p) == 1) {
                order /= fact.base;
            } else {
                break;
            }
        }
    }
    return order;
}

/**
 * For the fraction 1/n, compute the period of the repeating decimal and the
 * offset, i.e. the number of digits after the decimal point before the period
 * starts.
 */
std::pair<int, int> decimal_period_and_offset(
    int n, const std::unordered_map<int, int>& periods, const std::vector<int>& prime_factor_sieve)
{
    // First, compute the offset. this is given by max(a, b) where the prime
    // factorization of n contains 2^a * 5^b.
    int powers_of_2 = 0;
    while (n % 2 == 0) {
        n /= 2;
        powers_of_2++;
    }
    int powers_of_5 = 0;
    while (n % 5 == 0) {
        n /= 5;
        powers_of_5++;
    }

    const int offset = std::max(powers_of_2, powers_of_5);
    if (n == 1) {
        return {0, offset};
    }

    // Next, we compute the period.
    // For primes p, the period is Tp and was previously calculated in `periods`.
    // For prime powers p^k, the period is p^{k-1} * Tp
    // EXCEPT when p = 3, 487, or 56598313, in which case the period is p^{k-2} * Tp.
    // For composite n, the period is the LCM of the periods of its prime power factors.
    int period = 1;
    const auto facts = mf::prime_factorize(n, prime_factor_sieve);
    for (const auto& fact : facts) {
        int fact_period = periods.at(fact.base);
        if ((fact.exp > 1) && (fact.base == 3 || fact.base == 487 || fact.base == 56598313)) {
            fact_period *= mf::pow(fact.base, fact.exp - 2);
        } else {
            fact_period *= mf::pow(fact.base, fact.exp - 1);
        }
        period = std::lcm(period, fact_period);
    }
    return {period, offset};
}

/**
 * Get the kth digit of the decimal expansion of 1/n. k must be greater than 0.
 */
int get_decimal_digit(int n, int k)
{
    assert(k > 0);
    const int x = mf::modular_power(10, k - 1, n);
    return (x * 10) / n;
}

long p820()
{
    const int limit = 10'000'000;

    const auto prime_factor_sieve = mf::prime_factor_sieve(limit + 1);

    // compute periods of 1/p for all primes p
    std::unordered_map<int, int> periods;
    for (int p = 3; p <= limit; p += 2) {
        if (prime_factor_sieve[p] != p || p == 5) {
            continue;
        }
        const int order = order_of_10(p, prime_factor_sieve);
        periods[p] = order;
    }

    // compute limit-th digit for all n
    int total = 0;
    for (int i = 1; i <= limit; i++) {
        const auto [period, offset] = decimal_period_and_offset(i, periods, prime_factor_sieve);
        if (period == 0) {
            assert(offset < limit);  // make sure the digit is 0
            continue;
        }

        int place = (limit - offset) % period;
        if (place == 0) {
            place += period;
        }
        place += offset;

        total += get_decimal_digit(i, place);
        ;
    }
    return total;
}

int main()
{
    printf("%ld\n", p820());
}
