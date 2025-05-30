#include <numeric>
#include <vector>

/*

Forgetting about Gaussian integers, the sum of the divisors of n for all
1 <= n <= N is given by

    sum_{n=1}^{N} n * floor(N/n)

If we include Gaussian integers, we just need to change the `n` factor in the
sum to include each time we are able to write n = k(a^2 + b^2) for coprime a, b.
We use a sieve method to generate how these `n` factors change.

ANSWER 17971254122360635

*/

long p153()
{
    const int limit = 100'000'000;

    // initialize sieve
    std::vector<long> sieve(limit + 1);
    for (int i = 0; i <= limit; i++) {
        sieve[i] = i;
    }

    // iterate over all a, b coprime
    for (int a = 1; a * a < limit; a++) {
        for (int b = 1; b <= a; b++) {
            if (std::gcd(a, b) == 1) {
                int norm = a * a + b * b;
                for (int k = 1; k * norm <= limit; k++) {
                    sieve[k * norm] += (a == b ? 2 * a : 2 * (a + b)) * k;
                }
            }
        }
    }

    // do sum over divisors with new sieve values
    long sum = 0;
    for (int i = 1; i <= limit; i++) {
        sum += sieve[i] * (limit / i);
    }

    return sum;
}

int main()
{
    printf("%ld\n", p153());
}
