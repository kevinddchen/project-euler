#include <numeric>
#include <vector>

#include <cassert>

/*

The radical can be precomputed quite efficiently using a sieve.

ANSWER 18407904

*/

std::vector<int> radical_sieve(int size)
{
    assert(size >= 0);

    // initialize sieve
    std::vector<int> sieve(size);
    for (int i = 0; i < size; i++) {
        sieve[i] = 1;
    }

    // sieve
    for (int i = 2; i < size; i++) {
        if (sieve[i] == 1) {
            for (int j = i; j < size; j += i) {
                sieve[j] *= i;
            }
        }
    }
    return sieve;
}

long p127()
{
    constexpr int limit = 120'000;

    const auto rad = radical_sieve(limit);

    long count = 0;
    for (int c = 1; c < limit; c++) {
        // skip c if it does not have enough duplicate factors
        if (2 * rad[c] >= c) {
            continue;
        }

        for (int a = 1; a <= (c - 1) / 2; a++) {
            const int b = c - a;

            if (static_cast<long>(rad[a]) * static_cast<long>(rad[b]) < c / rad[c] && std::gcd(a, b) == 1 &&
                std::gcd(a, c) == 1 && std::gcd(b, c) == 1) {
                count += c;
            }
        }
    }

    return count;
}

int main()
{
    printf("%ld\n", p127());
}
