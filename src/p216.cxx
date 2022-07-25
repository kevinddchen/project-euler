#include <cstdio>
#include <ctime>


/*

We can use a sieve method to generate all primes. This relies on two claims:

 1. If d is a non-trivial (i.e. d =/= 1) divisor of t(n) = 2n^2 - 1, then
    (a) d does not divide n, n+1, or n-1. Equivalently, for no integer k will
        n + kd be 0 or +/- 1.
    (b) d divides t(+/- n + k d) for all integer k.

(Proof) For (a), note that d cannot divide 1 and t(n) = 2(n +/- 1)^2 -/+ 4(n +/-1) + 1.
For (b), note that t(+/- n + k d) = t(n) +/- 4 n k d + 2 k^2 d^2.

 2. Let d be the smallest non-trivial divisor of t(n) = 2n^2 - 1. If d =/= t(n)
    then d divides t(n') for some 2 <= n' < n.

(Proof) First, we prove that d < 2n. Since d is the smallest non-trivial
divisor of t(n) but d =/= t(n), we necessarily have d^2 <= t(n).
    d^2 <= t(n) = 2n^2 - 1 < 2n^2  -->  d < sqrt(2) n < 2 n
This implies |n - d| < n. From Claim 1a, we also have 2 <= |n - d|. From Claim
1b, d divides t(|n-d|).

The sieve works as follows: starting from n=2, by Claim 2 we know that t(2) = 7
is prime. Then all n = 7-2, 7+2, 14-2, 14+2, ... correspond to composite t(n).
So t(3) and t(4) are prime and t(5) is composite. For each composite we
encounter, if it contains a factor that we have not encountered before, we apply
the same procedure to find more composites. For instance, t(9) = 7 * 23 is
composite and 23 has not been encountered before. Then all n = 23-9, 23+9, 46-9,
46+9, ... correspond to composite t(n).

ANSWER 5437849

*/


/* Divide out t=sieve[n] from indices t-n, t+n, 2t-n, 2t+n, ... */
void filter_multiples(long * sieve, int limit, long n)
{
    long a = sieve[n]-n, b = sieve[n]+n, temp;
    while (a <= limit)
    {
        while (sieve[a] % sieve[n] == 0)
            sieve[a] /= sieve[n];
        temp = a+sieve[n];
        a = b;
        b = temp;
    }
}


long p216()
{
    const int limit = 50'000'000;

    // initialize sieve
    long * sieve = new long[limit+1];
    for (long n=0; n<=limit; n++)
        sieve[n] = 2*n*n - 1;

    long C = 0;
    for (long n=2; n<=limit; n++)
    {
        if (sieve[n] == 1)          // t(n) has no new factors
            continue;
        if (sieve[n] == 2*n*n-1)    // t(n) is prime
            C++;
        filter_multiples(sieve, limit, n);
    }
    return C;
}


int main()
{
    clock_t t;
    t = clock();
    printf("%ld\n", p216());
    t = clock()-t;
    printf("Time: %.3f\n", ((float) t)/CLOCKS_PER_SEC);
}
