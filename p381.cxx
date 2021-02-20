// p381.cxx
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include "cmathfuncs.h"
using namespace std;

/*

See solution explanations.

ANSWER 139602943319822

*/

long int p381() {

    long int size = 100000000;
    bool * sieve = primeSieve(size);

    long int S = 0;
    long int n;
    for (long int i=2; i<size; i++) {
        if (sieve[i]) {
            
            n = (-3*modularInverse(8, i))%i;
            if (n < 0)
                n += i;
            S += n;
        }
    }
    return S;
}

int main() {
    clock_t t;
    t = clock();
    printf("%ld\n", p381());
    t = clock()-t;
    printf("Time: %.3f\n", ((float) t)/CLOCKS_PER_SEC);
}


