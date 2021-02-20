// p73.cxx
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include "cmathfuncs.h"
using namespace std;

/*

Very similar to Problem 71.

ANSWER 7295372

*/

long int p73() {
    
    long int C = 0;

    int p_0;
    for (int q=4; q<12001; q++) {
        p_0 = (int) (q-1.)/3 + 1;       // p/q just over 1/3
        for (int p=p_0; p*2<q; p++) {   // while p/q less than 1/2
            if (gcd(p, q) == 1) {       // check fraction reduced
                C++;
            }
        }
    }
    return C;
}

int main() {
    clock_t t;
    t = clock();
    printf("%ld\n", p73());
    t = clock()-t;
    printf("Time: %.3f\n", ((float) t)/CLOCKS_PER_SEC);
}

