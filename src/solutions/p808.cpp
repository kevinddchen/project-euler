#include <mf/mathfuncs.hpp>

/*

Brute force.

ANSWER 3807504276997394

*/

/*
 * Reverse an integer in base 10.
 */
long reverse(long x)
{
    long y = 0;
    while (x > 0) {
        y = y * 10 + x % 10;
        x /= 10;
    }
    return y;
}

long p808()
{
    constexpr int limit = 50;

    int count = 0;
    long sum = 0;

    long x = 1;
    while (count < limit) {
        x += 2;

        const long sq = x * x;
        const long rev = reverse(sq);

        // cannot be a palindrome
        if (sq == rev) {
            continue;
        }

        const long y = (long)sqrt(rev);

        // if   (i) rev is a perfect square
        //      (ii) x is prime
        //      (iii) y is prime
        if (y * y == rev && mf::is_prime(x) && mf::is_prime(y)) {
            count++;
            sum += sq;
        }
    }
    return sum;
}

int main()
{
    printf("%ld\n", p808());
}
