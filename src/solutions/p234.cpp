#include "mf/mathfuncs.hpp"

/*

We iterate over all primes up to 999983 ~ sqrt(999966663333). For each pair of
consecutive primes p and q, the following lists of integers are semidivisible:

    p(p+1), p(p+2), ..., excluding pq and up to q^2
    q(q-1), q(q-2), ..., excluding pq and down to p^2

This gives all the semidivisible numbers up to 999983^2. Thankfully, there are
no semidivisible numbers between 999983^2 and 999966663333, which can be
checked.

ANSWER 1259187438574927161

*/

long p234()
{
    const long limit = 999'966'663'333;

    const long sqrt_limit = sqrt(limit);

    // generate primes up to and including `sqrt_limit`
    std::vector<long> primes;
    {
        const std::vector<bool> sieve = mf::prime_sieve(sqrt_limit + 1);
        for (int i = 2; i < static_cast<int>(sieve.size()); ++i) {
            if (sieve[i]) {
                primes.push_back(i);
            }
        }
    }

    // iterate over pairs (p, q) of consecutive primes
    long sum = 0;
    for (int prime_idx = 0; prime_idx < static_cast<int>(primes.size()) - 1; ++prime_idx) {
        const long p = primes[prime_idx];
        const long q = primes[prime_idx + 1];

        // p(p+1), p(p+2), ... excluding pq
        for (long a = p + 1; p * a < q * q; ++a) {
            if (a == q) {
                continue;
            }
            sum += p * a;
        }

        // q(q-1), q(q-2), ... excluding pq
        for (long a = q - 1; q * a > p * p; --a) {
            if (a == p) {
                continue;
            }
            sum += q * a;
        }
    }

    return sum;
}

int main()
{
    printf("%ld\n", p234());
}
