#include "common.h"
#include "mathfuncs.h"

/*

Brute force. It is easier to work with logarithms,
    p log q + q log p <= 800800 log 800800

ANSWER 1412403576

*/

long p800()
{
    constexpr int N = 800800;
    const double NlogN = N * log(N);

    const int limit = NlogN / log(2);
    const auto sieve = mf::prime_sieve(limit + 1);

    // create vector of primes
    std::vector<long> primes;
    for (long p = 2; p <= limit; p++) {
        if (sieve[p]) {
            primes.push_back(p);
        }
    }

    // let p be the smallest prime and q be the largest.
    // we increment p and decrement q until we meet in the middle.
    int count = 0;
    auto lower = primes.begin();
    auto upper = primes.end() - 1;
    while (true) {
        while (*lower * log(*upper) + *upper * log(*lower) > NlogN) {
            upper--;
        }
        // break if we have reached the middle
        if (lower >= upper) {
            break;
        }
        count += upper - lower;
        lower++;
    }

    return count;
}

int main()
{
    TIMED(printf("%ld\n", p800()));
}
