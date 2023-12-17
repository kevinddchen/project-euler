#include "common.h"

/*

First, we note that aside from pi(1) = 1 and pi(2) = 3, pi(n) is even for all
values of n. So M(3) = 2 and M(p) = 1 for all odd other p. We just need to
compute M(p) for even p.

By definition of the Pisano period, if pi(n) = p then Fib(p) = 0 (mod n) and
Fib(p+1) = 1 (mod n). This implies that n divides gcd(Fib(p), Fib(p+1)-1).
There are two cases:
 -  p = 4k:     n divides Fib(2k).
 -  p = 4k + 2: n divides Lucas(2k + 1).

Thus, we just need to compute the first 500,000 Fibonacci and Lucas numbers,
mod 1,234,567,891.

ANSWER 29894398

*/

long p854()
{
    const long mod = 1'234'567'891;
    const long n = 1'000'000;

    long fib = 0;  // tracks Fib(p / 2)
    long fib_prev = 1;

    long lucas = 2;  // tracks Lucas(p / 2)
    long lucas_prev = -1;

    long prod = 2;  // to account for M(3) = 2
    for (int p = 2; p <= n; p += 2) {
        // compute next fibonacci and lucas numbers
        const long fib_next = (fib + fib_prev) % mod;
        const long lucas_next = (lucas + lucas_prev) % mod;

        fib_prev = fib;
        fib = fib_next;

        lucas_prev = lucas;
        lucas = lucas_next;

        // multiply product by lucas or fib
        const long half = p / 2;
        if (half % 2 == 0) {
            prod = (prod * fib) % mod;
        } else {
            prod = (prod * lucas) % mod;
        }
    }

    return prod;
}

int main()
{
    printf("%ld\n", p854());
}
