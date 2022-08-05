#include <cstdio>
#include <ctime>

/*

Each hidden point a taxicab distance n away from the center corresponds to a
pair of integers (a, b) where a+b = n and gcd(a, b) =/= 1. Thus we are summing
up, for each n, the number of a < n that share a non-trivial divisor with n.
This is given precisely by n - phi(n) - 1, where phi is the totient function.

ANSWER 11762187201804552

*/

/* Taken from p69. */
int *totient_sieve(int size)
{
    int *sieve = new int[size];
    // initialize values
    for (int i = 2; i < size; i++)
        sieve[i] = i;
    // sieve
    for (int i = 2; i < size; i++)
    {
        if (sieve[i] == i) // i is prime
        {
            sieve[i] -= 1;
            for (int j = 2 * i; j < size; j += i)
                sieve[j] = (sieve[j] / i) * (i - 1);
        }
    }
    return sieve;
}

long p351()
{
    const int size = 100'000'000;
    long S = size - 1;

    int *sieve = totient_sieve(size + 1);
    for (int i = 2; i <= size; i++)
        S += i - sieve[i] - 1;

    return S * 6;
}

int main()
{
    clock_t t;
    t = clock();
    printf("%ld\n", p351());
    t = clock() - t;
    printf("Time: %.3f\n", ((float)t) / CLOCKS_PER_SEC);
}
