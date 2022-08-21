#include "common.h"

#include <memory>

/*

Each hidden point a taxicab distance n away from the center corresponds to a
pair of integers (a, b) where a+b = n and gcd(a, b) =/= 1. Thus we are summing
up, for each n, the number of a < n that share a non-trivial divisor with n.
This is given precisely by n - phi(n) - 1, where phi is the totient function.

ANSWER 11762187201804552

*/

/* Taken from p69. */
std::unique_ptr<int[]> totient_sieve(int size)
{
    auto sieve = std::make_unique<int[]>(size);
    // initialize values
    for (int i = 2; i < size; i++)
    {
        sieve[i] = i;
    }
    // sieve
    for (int i = 2; i < size; i++)
    {
        if (sieve[i] == i) // i is prime
        {
            sieve[i] -= 1;
            for (int j = 2 * i; j < size; j += i)
            {
                sieve[j] = (sieve[j] / i) * (i - 1);
            }
        }
    }
    return sieve;
}

long p351()
{
    const int size = 100'000'000;
    long count = size - 1;

    auto sieve = totient_sieve(size + 1);
    for (int i = 2; i <= size; i++)
    {
        count += i - sieve[i] - 1;
    }

    return count * 6;
}

int main()
{
    TIMED(printf("%ld\n", p351()));
}
