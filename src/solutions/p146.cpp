#include <mf/mathfuncs.hpp>

#include <array>

/*

More or less brute force. We know that primes are = +/- 1 (mod 6), so we check
that n^2 + 1, n^2 + 3, n^2 + 7, n^2 + 9, n^2 + 13, and n^2 + 27 are all prime,
and that n^2 + 15, n^2 + 19, n^2 + 21, and n^2 + 25 are all composite.

We use a prime sieve to generate the primes. We also only need to use p >= 5
when checking primality.

ANSWER 676333270

*/

bool check(long n, const std::vector<long>& primes)
{
    const long n2 = n * n;
    const std::array<long, 6> possible_primes = {n2 + 1, n2 + 3, n2 + 7, n2 + 9, n2 + 13, n2 + 27};
    const std::array<long, 4> possible_composite = {n2 + 15, n2 + 19, n2 + 21, n2 + 25};

    // check that possible primes are prime
    for (long p : primes) {
        if (p * p > n2 + 27) {
            break;
        }
        for (long pp : possible_primes) {
            if (pp % p == 0) {
                return false;
            }
        }
    }

    // check that possible composites are composite
    for (long pc : possible_composite) {
        bool is_prime = true;
        for (long p : primes) {
            if (p * p > pc) {
                break;
            }
            if (pc % p == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) {
            return false;
        }
    }
    return true;
}

long p146()
{
    const long limit = 150'000'000;

    // generate primes (excluding 2 and 3) up to `limit`
    std::vector<long> primes;
    {
        const auto sieve = mf::prime_sieve(limit);
        for (int i = 5; i < limit; i += 2) {
            if (sieve[i]) {
                primes.push_back(i);
            }
        }
    }

    long sum = 0;
    // iterate over all n where n = 2 or 4 (mod 6)
    // note that 150'000'000 is divisible by 6
    for (long i = 0; i < limit; i += 6) {
        for (long n : {i + 2, i + 4}) {
            if (check(n, primes)) {
                sum += n;
            }
        }
    }

    return sum;
}

int main()
{
    printf("%ld\n", p146());
}
