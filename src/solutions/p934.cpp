#include "mf/mathfuncs.hpp"

/*

The general strategy is instead of doing the brute-force computation, instead we figure out, given a prime p, the values
of n <= limit where u(n) = p. This is best demonstrated by looking for the pattern.

First, we note that u(n) = 2 for all odd n. This means that for all even n, u(n) > 2.

Of the even n, we note that u(n) = 3 for all n = 2, 4 (mod 6). This means that for all n = 0 (mod 6), u(n) > 3.

With this we can start to see a pattern emerge:
 - u(n) = 5 for all n = 6, 12, 18, 24 (mod 30)
 - u(n) = 7 for all n = 30, 60, 90, 120, 150, 180 (mod 210)

However, when we look at p=11, we see a new emergent phenomenon. We note that at this moment of time we are
only considering n = 0 (mod 210). We can note that u(n) = 11 for all n = 210, 420, 630, ... (mod 2310) but NOT for
n = 1470 (mod 2310) because 1470 % 11 = 7 is divisible by 7. This means that when we are looking at p=13, we are
considering n = 0 and 1470 (mod 2310). In fact, as the primes we consider increase, the number of "remainders" we have
to consider also increase. For example, for p=17 we are considering n = 0, 13020, 18480, and 24570 (mod 30030).

ANSWER 292137809490441370

*/

/**
 * Compute the sum by brute force: compute u(n) for each n.
 */
long brute_force(long limit, const std::vector<long>& primes)
{
    long sum = 0;
    for (long n = 1; n <= limit; ++n) {
        // compute u(n)
        bool found = false;
        for (long prime : primes) {
            if ((n % prime) % 7 != 0) {
                sum += prime;
                found = true;
                break;
            }
        }
        if (!found) {
            throw std::runtime_error("Not enough primes!");
        }
    }

    return sum;
}

/**
 * Compute the sum in a smarter way: for each p, find all n <= limit where u(n) = p.
 */
long smarter(long limit, const std::vector<long>& primes)
{
    long sum = 0;

    long prev_mod = 1;
    std::vector<long> prev_rems = {0};

    for (long prime : primes) {
        long count = 0;  // counts `n` where `u(n) = prime`

        const long mod = prev_mod * prime;
        //  we have `n` of the form `prev_mod * k + prev_rem`. with the new `mod = prev_mod * prime`, we want to figure
        //  out the new `rem` such that `n % prime` is divisible by 7. then all `n` not of the form `mod * k + rem` will
        //  have `u(n) = prime`.
        std::vector<long> rems;
        for (long prev_rem : prev_rems) {
            // HACK: if `prime==53`, then `mod` has overflown. thus for larger primes, we should only accept k=0
            const long k_upper_bound = (prime > 53 ? 1 : prime);
            for (long k = 0; k < k_upper_bound; ++k) {
                const long n = prev_mod * k + prev_rem;
                if (n > limit) {
                    break;
                }
                if ((n % prime) % 7 == 0) {
                    rems.push_back(n % mod);
                } else {
                    // how many `prev_mod * (k + l * prime) + prev_rem` for l = 0, 1, ... are <= limit?
                    count += 1 + ((limit - prev_rem) / prev_mod - k) / prime;
                }
            }
        }

        sum += prime * count;

        prev_mod = mod;
        prev_rems = std::move(rems);
    }

    if (prev_rems.size() != 1) {
        throw std::runtime_error("Not enough primes!");
    }
    return sum;
}

long p934()
{
    // constexpr long LIMIT = 1470;
    constexpr long LIMIT = 1e17;

    // generate a handful of primes; error handling will tell us when we don't have enough...
    const auto sieve = mf::prime_sieve(100);
    std::vector<long> primes;
    for (long p = 2; p < static_cast<long>(sieve.size()); ++p) {
        if (sieve[p]) {
            primes.push_back(p);
        }
    }

    // const long brute_force_answer = brute_force(LIMIT, primes);
    // printf("%ld (brute force answer)\n", brute_force_answer);

    return smarter(LIMIT, primes);
}

int main()
{
    printf("%ld\n", p934());
}
