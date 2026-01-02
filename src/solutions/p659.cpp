#include "mf/mathfuncs.hpp"

/*

From some initial experimentation, we found that P(k) is equal to the largest
prime factor of 4k^2 + 1. But this takes too long to compute directly, so we
had to investigate a little further.

Given some k, we need to find p, n such that p | n^2 + k^2 and (n+1)^2 + k^2.
Thus p | 2n+1. But since we can subtract p from n, i.e. p | (n-p)^2 + k^2, we
have an initial 0 < m <= p and thus p = 2m+1. Then p | n^2 + k^2 and
(n+1)^2 + k^2 for all n = m, m+p, m+2p, ...

How do we find the p = 2m+1 such that p | m^2 + k^2?
    If m even: m^2 = (m/2)(2m+1) - m/2  -->  k^2 = m/2 (mod p)
    If m odd: m^2 = (m-1)/2 (2m+1) + (m+1)/2  -->  k^2 = -(m+1)/2 (mod p)
An infinite number of solutions exist for k when the square root exists. By
looking at tables of Legendre symbols, we hypothesized that solutions for k
only exist for m even. So we can iterate through values of m:

m  | p  | k (mod p)
-----------------
2  | 5  | +/- 1
6  | 13 | +/- 4
8  | 17 | +/- 2
14 | 29 | +/- 6
...

But this is difficult to compute, since we need to check that p is prime and
then need to compute the square root mod p. Instead, we iterate through values
of k and use the periodicity in p.

k = 1, p = 4k^2 + 1 = 5 ... this divides for all k = +/- 1 mod p
                            i.e. for k = 4, 6, 9, 11, 14, ...
k = 2, p = 17 ...           this divides for all k = 15, 19, ...
k = 3, p = 37 ...           this divides for all k = 34, 40, ...
k = 4, p = 65 ... X this is not prime! but we marked 5 as a divisor previously,
                    so we find 65 / 5 = 13 to be a new prime factor.

This is quite efficient since it is just a sieve.

ANSWER 238518915714422000

*/

long p659()
{
    const int target = 10'000'000;
    const long mod = 1'000'000'000'000'000'000;

    // initialize array of potential_ps
    std::vector<long> potential_ps(target + 1);
    for (long k = 1; k <= target; k++) {
        potential_ps[k] = 4 * k * k + 1;
    }

    // initialize array of largest prime factors
    // std::array<long, target + 1> largest_prime_factors;
    std::vector<long> largest_prime_factors(target + 1);
    for (long k = 1; k <= target; k++) {
        largest_prime_factors[k] = -1;  // sentinel value for not yet computed
    }

    // sieve
    long total = 0;
    for (long k = 1; k <= target; k++) {
        const long pot_p = potential_ps[k];

        long p;
        bool skip_sieve;
        if (pot_p == 1) {  // no new prime encountered
            p = largest_prime_factors[k];
            skip_sieve = true;
        } else {
            p = std::max(largest_prime_factors[k], pot_p);
            skip_sieve = false;
        }

        total = (total + p) % mod;

        if (skip_sieve) {
            continue;
        }

        // visit all next_k = +/- k mod p.
        long next_k = p - k;
        long next_next_k = p + k;
        while (next_k <= target) {
            largest_prime_factors[next_k] = std::max(largest_prime_factors[next_k], p);

            // divide out all multiples of p
            while (potential_ps[next_k] % p == 0) {
                potential_ps[next_k] /= p;
            }

            // determine next value for next_p
            const long tmp = next_k;
            next_k = next_next_k;
            next_next_k = tmp + p;
        }
    }

    return total;
}

int main()
{
    printf("%ld\n", p659());
}
