#include <cstdio>
#include <ctime>
#include "mathfuncs.h"


/*

See solution explanations.

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


