// p214.cxx
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include "cmathfuncs.h"
using namespace std;

/*

Use a sieve to calculate totients, like in Problem 69, and then replace old
values with the chain length.

ANSWER 1677366278943

*/

long int p214() {

    long int size = 40000000;
    long int target = 25;

    long int S = 0;

    //initialize array
    long int * sieve = new long int[size];
    for (long int i=0; i<size; i++) {
        sieve[i] = i;
    }

    long int tot;
    for (long int i=2; i<size; i++) {
        tot = sieve[i];
        //multiply further totients
        if (i == tot) {     // is prime
            tot--;
            for (long int j=i; j<size; j+=i) {
                sieve[j] /= i;
                sieve[j] *= i-1;
            }
            if (sieve[tot]+1 == target) {
                S += i;
            }
        }
        sieve[i] = sieve[tot]+1;
    }

    return S;
}

int main() {
    clock_t t;
    t = clock();
    printf("%ld\n", p214());
    t = clock()-t;
    printf("Time: %.3f\n", ((float) t)/CLOCKS_PER_SEC);
}


