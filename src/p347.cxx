#include <cstdio>
#include <ctime>
#include <algorithm>
#include "mathfuncs.h"
#include <iostream>


/*

Brute force.

ANSWER 11109800204052

*/


long M(long p, long q, long N) 
{
    long A, B;
    long ans = 0;

    A = p*q;
    while (A <= N) 
    {
        B = A;
        while (B*q <= N)
            B *= q;
        ans = std::max(ans, B);
        A *= p;
    }

    return ans;
}
            

long p347() 
{
    const int N = 10000000;

    // get primes
    bool * sieve = prime_sieve(N/2);
    std::vector<int> primes;
    for (int i=0; i<N/2; i++) 
    {
        if (sieve[i])
            primes.push_back(i);
    }

    // calculate M(p, q, N) for primes p < q
    std::vector<int>::iterator p_iter, q_iter;
    long M_ans, sum = 0;
    for (p_iter = primes.begin(); p_iter != primes.end(); p_iter++) 
    {
        for (q_iter = p_iter+1; q_iter != primes.end(); q_iter++) 
        {
            M_ans = M(*p_iter, *q_iter, N);
            if (M_ans == 0)
                break;
            sum += M_ans;
        }
    }
    return sum;
}


int main() 
{
    clock_t t;
    t = clock();
    printf("%ld\n", p347());
    t = clock()-t;
    printf("Time: %.3f\n", ((float) t)/CLOCKS_PER_SEC);
}
