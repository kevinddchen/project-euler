#include "common.h"

/*

Hypothesis:
 -  pi(p^m)         = p^(m-1) * pi(m)
 -  pi(p^m * q^n)   = lcm( pi(p^m) , pi(q^n) )

ANSWER 44511058204

*/

/**
 * Computes the Pisano period using brute force. If the period is > limit,
 * returns -1.
 */
long compute_brute_force(long n, long limit)
{
    long a = 1;  // Fib i
    long b = 0;  // Fib i-1

    for (long i = 1; i <= limit; ++i) {
        long c = (a + b) % n;
        b = a;
        a = c;
        if (a == 1 && b == 0) {
            return i;
        }
    }
    return -1;
}


long p853()
{
    const long limit = 1'000'000'000;
    const long target = 120;

    long sum = 0;
    for (long n = 2; n < limit; ++n) {
        if (compute_brute_force(n, target) == target) {
            printf("%ld\n", n);
            sum += n;
        }
    }

    return sum;
}

int main()
{
    printf("%ld\n", p853());
}
