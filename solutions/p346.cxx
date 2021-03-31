// p346.cxx
#include <stdio.h>
#include <iostream>
#include <set>
#include <math.h>
#include <time.h>
#include "cmathfuncs.h"
using namespace std;

/*

Brute force. Note that any number n is 11 in base n-1. With this in mind, we
just enumerate all numbers for all bases up to 10^6, checking for repeats.

ANSWER 336108797689259276

*/



long long p346() {

    long long limit = 1000000000000;
    long long sum = 1;

    set<long long> S;
    set<long long>::iterator it;

    for (long long i=2; i*i <= limit; i++) {

        long long x = (i + 1)*i + 1;
        
        while (x < limit) {

            it = S.find(x);
            if (it == S.end()) {    // if x has not been encountered yet

                sum += x;
                S.insert(x);

            }

            x = x*i + 1;

        }
    }

    return sum;

}

int main() {
    clock_t t;
    t = clock();
    printf("%lld\n", p346());
    t = clock()-t;
    printf("Time: %.3f\n", ((float) t)/CLOCKS_PER_SEC);
}
