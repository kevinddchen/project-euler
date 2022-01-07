#include <cstdio>
#include <ctime>
#include "mathfuncs.h"


/*

Wilson's Theorem states that for prime p, we have (p-1)! = -1 (mod p). Thus we
can deduce that (p-2)! = 1, (p-3)! = -1/2, (p-4)! = 1/6, and (p-5)! = -1/24 (mod
p). Fractions are to be interpreted as modular inverses, since Z_p is a field.
Thus S(p) = -3/8 (mod p).

ANSWER 139602943319822

*/


long p381() 
{
    const int size = 100000000;
    bool * sieve = prime_sieve(size);

    long S = 0;
    long n;
    for (long i=2; i<size; i++) 
    {
        if (sieve[i]) 
        {
            n = (-3*modular_inverse(8L, i))%i;
            if (n < 0)
                n += i;
            S += n;
        }
    }
    return S;
}


int main() 
{
    clock_t t;
    t = clock();
    printf("%ld\n", p381());
    t = clock()-t;
    printf("Time: %.3f\n", ((float) t)/CLOCKS_PER_SEC);
}


