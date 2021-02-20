// p407.cxx
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include "cmathfuncs.h"
using namespace std;


/*

See solution explanations.

ANSWER 39782849136421

*/


int modularInverse(int a, int n) {
    /* Return b such that ab = 1 (mod n). */

    int s = 0, old_s = 1, new_s;
    int t = 1, old_t = 0, new_t;
    int r = n, old_r = a, new_r;

    while (r != 0) {

        int q = old_r / r;
        new_r = old_r - q*r;
        new_s = old_s - q*s;
        new_t = old_t - q*t;
        old_r = r;
        old_s = s;
        old_t = t;
        r = new_r;
        s = new_s;
        t = new_t;

    }

    if (old_r > 1)
        return 0;
    return (old_s+n)%n;

}





short * factorSieve(int size) {
    /* Create prime sieve of smallest prime factor. */

    short * sieve = new short[size+1]();
    sieve[0] = sieve[1] = 1;

    for (int i=2; i<= size; i++) {
        if (sieve[i]==0) {

            for (int j=i*i; j<=size; j+=i) {

                if (sieve[j] == 0)
                    sieve[j] = i;

            }
        }
    }

    return sieve;
}        





vector<int> primeSieveFactorize(int x, short * sieve) {
    /* Returned vector of prime factor / multiplicity. */

    vector<int> facts;

    while (sieve[x] >= 2) {

        int i = sieve[x];
        int c = 0;

        while (sieve[x] == i or x == i) {
            x /= i;
            c++;
        }

        facts.push_back(i);
        facts.push_back(c);
    }

    if (sieve[x] == 0) {
        facts.push_back(x);
        facts.push_back(1);

    }
    return facts;
}





int maxIdem(int * arr, int size, int N, int i=0, int running_sum=0) {
    /* Recursively find largest idempotent. */

    if (i == size)
        return running_sum % N;

    return max( maxIdem(arr, size, N, i+1, running_sum), 
                maxIdem(arr, size, N, i+1, running_sum+arr[i]) );

}





long long p407() {

    int size = 10000000;
    short * sieve = factorSieve(size);

    long long sum_idem = 0;

    for (int N=2; N<=size; N++) {

        // prime factorize
        vector<int> factors = primeSieveFactorize(N, sieve);

        // find base idempotents
        int num_idems = factors.size()/2;
        int m, b, a;
        int * idems = new int [num_idems];
        for (int i=0; i<num_idems; i++) {

            m = pow( factors[2*i], factors[2*i+1] );
            b = N / m;
            a = modularInverse(b, m) * b;

            idems[i] = a;

        }

        // find largest idempotent
        sum_idem += maxIdem(idems, num_idems, N);
    }

    return sum_idem;
}



int main() {
    clock_t t;
    t = clock();
    printf("%lld\n", p407());
    t = clock()-t;
    printf("Time: %.3f\n", ((float) t)/CLOCKS_PER_SEC);
}
