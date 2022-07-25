#include <cstdio>
#include <ctime>
#include "mathfuncs.h"


/*

A PGI (prime generating integers) must be square-free, i.e. have a prime
factorization with no powers greater than 1.

ANSWER 1739023853137

*/


bool prime_generating(long x, long * div_arr, bool * sieve)
{
    div_arr[0] = 1;
    int divs = 1;
    if (!sieve[x+1])        // 1 is divisor, so x+1 must be prime
        return false;

    for (long int p=2; p*p <= x; p++)   // find prime factors
    {
        if (sieve[p] and x%p==0)
        {
            if (x%(p*p)==0)             // x must be square-free
                return false;

            int add = 0;
            for (int i=0; i < divs; i++)
            {
                long int d = p*div_arr[i];
                if (d*d < x)
                {
                    if (!sieve[d + x/d])
                        return false;
                    div_arr[divs+add] = d;
                    add++;
                }
            }
            divs += add;
        }
    }
    return true;
}


long p357()
{
    const int size = 100000000;
    bool * sieve = prime_sieve(size+2);

    //find prime_generating
    long S = 0;
    long div_arr[100];

    for (long i=1; i<=size; i++)
    {
        if (prime_generating(i, div_arr, sieve))
            S += i;
    }
    return S;
}


int main()
{
    clock_t t;
    t = clock();
    printf("%ld\n", p357());
    t = clock()-t;
    printf("Time: %.3f\n", ((float) t)/CLOCKS_PER_SEC);
}
