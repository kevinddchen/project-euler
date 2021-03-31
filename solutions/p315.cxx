// p315.cxx
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include "cmathfuncs.h"
using namespace std;


/*

Brute force.

ANSWER 13625242

*/


long digitalRoot(long x) {

    if (x < 10)
        return 0;
    long root = 0;
    while (x != 0) {
        root += x%10;
        x /= 10;
    }
    return root;
}



bool ** clock(long n, bool digits [11][7]) {

    bool ** clock = new bool * [8];
    for (int i=0; i<8; i++) {

        if (n == 0)
            clock[i] = digits[10];
        else
            clock[i] = digits[n%10];
        n /= 10;

    }
    return clock;
}



int countOn(bool ** clock1, bool ** clock2) {

    int c = 0;
    for (int i=0; i<8; i++) {
        for (int j=0; j<7; j++) {
            if (clock1[i][j] and clock2[i][j])
                c++;
        }
    }
    return c;
}



long p315() {

    // construct digits
    bool digits [11][7] = {
        {1, 1, 1, 0, 1, 1, 1},
        {0, 0, 1, 0, 0, 1, 0},
        {1, 0, 1, 1, 1, 0, 1},
        {1, 0, 1, 1, 0, 1, 1},
        {0, 1, 1, 1, 0, 1, 0},
        {1, 1, 0, 1, 0, 1, 1},
        {1, 1, 0, 1, 1, 1, 1},
        {1, 1, 1, 0, 0, 1, 0},
        {1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 0, 1, 1},
        {0, 0, 0, 0, 0, 0, 0}   };

    // count transitions
    long c = 0;
    bool * sieve = primeSieve(20000000);
    for (long i=10000000; i<20000000; i++) {

        if (!sieve[i])
            continue;

        bool ** A = clock(i, digits);
        long j = digitalRoot(i);

        while (j > 0) {

            bool ** B = clock(j, digits);
            c += 2 * countOn(A, B);
            A = B;
            j = digitalRoot(j);

        }
    }

    return c;

}



int main() {
    clock_t t;
    t = clock();
    printf("%ld\n", p315());
    t = clock()-t;
    printf("Time: %.3f\n", ((float) t)/CLOCKS_PER_SEC);
}
