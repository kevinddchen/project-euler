#include <cstdio>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <vector>
#include <array>
#include "mathfuncs.h"


/*

See solution explanations.

ANSWER 39782849136421

*/


/* Computes sieve where nth entry is 
  - if n is composite: smallest prime factor of n.
  - if n is prime: 0.
*/
short * smallest_prime_factor(int N)
{
    // create sieve
    short * sieve = new short[N]();
    for (short i=2; i*i<N; i++) 
    {
        if (sieve[i] == 0) 
        {
            for (int j=i*i; j<N; j+=i) 
            {
                if (sieve[j] == 0)
                    sieve[j] = i;
            }
        }
    }
    return sieve;
}


/* Calculate prime factorization, with speed up from `smallest_prime_factors`. */
std::vector<std::array<int, 2>> prime_factorize(int x, short * sieve) 
{
    std::vector<std::array<int, 2>> facts;
    short p;
    int a;
    while (sieve[x] >= 2) 
    {
        p = sieve[x];
        a = 0;
        while (sieve[x] == p or x == p) 
        {
            x /= p;
            a++;
        }
        std::array<int, 2> arr = {p, a};
        facts.push_back(arr);
    }
    if (sieve[x] == 0)
    {
        std::array<int, 2> arr = {x, 1};
        facts.push_back(arr);
    }
    return facts;
}


int max_idem(int * arr, int size, int N, int i=0, int running_sum=0) 
{
    /* Recursively find largest idempotent. */

    if (i == size)
        return running_sum % N;

    return std::max(
        max_idem(arr, size, N, i+1, running_sum), 
        max_idem(arr, size, N, i+1, running_sum+arr[i]) 
    );
}


long p407() 
{
    const int size = 10'000'000;
    long sum_idem = 0;

    short * sieve = smallest_prime_factor(size+1);

    for (int n=2; n<=size; n++) 
    {
        // prime factorize
        std::vector<std::array<int, 2>> factors = prime_factorize(n, sieve);
    
        // find base idempotents
        int num_idems = factors.size();
        int m, b, a;
        int * idems = new int [num_idems];
        for (int i=0; i<num_idems; i++) 
        {
            m = pow(factors[i][0], factors[i][1]);
            b = n / m;
            a = modular_inverse(b, m) * b % n;
            idems[i] = a;
        }
        // find largest idempotent
        sum_idem += max_idem(idems, num_idems, n);
    }
    return sum_idem;
}


int main() 
{
    clock_t t;
    t = clock();
    printf("%ld\n", p407());
    t = clock()-t;
    printf("Time: %.3f\n", ((float) t)/CLOCKS_PER_SEC);
}
