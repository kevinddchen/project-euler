// p357.cxx
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include "cmathfuncs.h"
using namespace std;

/*

A PGI (prime generating integers) mustbe square-free, i.e. have a prime factorization
with no powers greater than 1.

ANSWER 1739023853137

*/

bool primeGenerating(long long x, long int * div_arr, bool * sieve) {
    div_arr[0] = 1;
    int divs = 1;
    if (!sieve[x+1]) {  // 1 is divisor, so x+1 must be prime
        return false;
    } 
    for (long int p=2; p*p <= x; p++) {  // find prime factors
        if (sieve[p] and x%p==0) {
            if (x%(p*p)==0) {   // x must be square-free
                return false;
            }
            int add = 0;
            for (int i=0; i < divs; i++) {
                long int d = p*div_arr[i];
                if (d*d < x) {
                    if (!sieve[d + x/d]) {
                        return false;
                    }
                    div_arr[divs+add] = d;
                    add++;
                }
            }
            divs += add;
        }
    }
    return true;
}


long int p357() {

    long int size = 100000000;
    bool * sieve = primeSieve(size+2);

    //find primeGenerating
    long int S = 0;
    long int div_arr[100];

    for (long int i=1; i<=size; i++) {
        if (primeGenerating(i, div_arr, sieve)) {
            S += i;
        }
    }

    return S;

}

int main() {
    clock_t t;
    t = clock();
    printf("%ld\n", p357());
    t = clock()-t;
    printf("Time: %.3f\n", ((float) t)/CLOCKS_PER_SEC);
}


