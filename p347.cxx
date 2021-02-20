// p347.cxx
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include "cmathfuncs.h"
using namespace std;

/*

Brute force.

ANSWER 11109800204052

*/



long M(long p, long q, long N) {

    long A, B;
    long ans = 0;

    A = p*q;
    while (A <= N) {

        B = A;
        while (B*q <= N) {
            B *= q;
        }
        ans = max(ans, B);
        A *= p;
    }

    return ans;
}
            

 
long p347() {

    long N = 10000000;

    // get primes
    bool * sieve = primeSieve(N/2);

    vector<int> primes;
    for (long i=0; i<=N/2; i++) {
        if (sieve[i]) 
            primes.push_back(i);
    }

    // calculate M(p, q, N) for primes p < q
    vector<int>::iterator p_iter, q_iter;
    long sum = 0;
    for (p_iter = primes.begin(); p_iter != primes.end(); p_iter++) {
        for (q_iter = p_iter+1; q_iter != primes.end(); q_iter++) {
             
            long M_ans = M(*p_iter, *q_iter, N);
            if (M_ans == 0)
                break;
            sum += M_ans;

        }
    }

    return sum;

}



int main() {
    clock_t t;
    t = clock();
    printf("%ld\n", p347());
    t = clock()-t;
    printf("Time: %.3f\n", ((float) t)/CLOCKS_PER_SEC);
}
