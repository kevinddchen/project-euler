#include <cstdio>
#include <ctime>
#include <vector>
#include "mathfuncs.h"


/*

First note that by the Chinese remainder theorem, solving m^e = m (mod pq)
is equivalent to solving

    a^e = a (mod p)     and     b^e = b (mod q)

where m = a (mod p) and m = b (mod q). 

We claim that the number of solutions to a^(e-1) = 1 (mod p) is equal to
gcd(e-1, p-1). Proof: since Z_p is cyclic, let g be a generator. Then a = g^n
(mod p) for some 0 <= n < p. If we let d = gcd(e-1, p-1) and p-1 = d*k, then we
note that since (e-1)*k is a multiple of p-1, we have

    (g^k)^(e-1) = g^((e-1)*k) = 1 (mod p)

The set { g^k, g^(2k), ... , g^((d-1)*k) } is the set of all solutions.

This implies that the number of solutions to a^e = a (mod p) is gcd(e-1, p-1)+1,
adding one to account for the solution a = 0.

Therefore, the number of solutions to m^e = m (mod pq) is equal to 

    (gcd(e-1, p-1) + 1) * (gcd(e-1, q-1) + 1)

Since p, q are odd and so is e (in order to be coprime to (p-1)(q-1), which is
even), the minimal value is actually (2+1)*(2+1) = 9. So we generate all e that
satisfy

    gcd(e, p-1) = gcd(e, q-1) = 1   and     gcd(e-1, p-1) = gcd(e-1, q-1) = 2

ANSWER 399788195976

*/


void filter(bool * sieve, int size, std::vector<std::array<int, 2>> pf)
{
    // Sieve out prime factors. If prime factor is 2, skip if power is =1,
    // otherwise sieve out multiples of 4.
    for (auto p : pf)
    {
        int multiple;
        if (p[0] == 2)
        {
            if (p[1] == 1)  // power = 1
                continue;
            multiple = 4;   // else power >= 2
        }
        else
            multiple = p[0];

        long k = multiple;
        while (k < size)
        {
            sieve[k] = false;
            k += multiple;
        }
    }
}


long p182() 
{
    const int p = 1009;
    const int q = 3643;
    const int phi = (p-1)*(q-1);

    // prime factorize p-1 and q-1
    auto p_factors = prime_factorize(p-1);
    auto q_factors = prime_factorize(q-1);

    // since p, q are odd, sieve to find e such that
    // odd e: true when gcd(e, p-1) = gcd(e, q-1) = 1
    // even e: true when gcd(e, p-1) = gcd(e, q-1) = 2
    bool * sieve = new bool[phi];
    // initialize sieve
    for (int i=0; i<phi; i++)
        sieve[i] = true;
    // sieve
    filter(sieve, phi, p_factors);
    filter(sieve, phi, q_factors);
    
    long S = 0;
    for (int i=3; i<phi; i+=2)
    {
        if (sieve[i] && sieve[i-1])
            S += i;
    }
       
    return S;
}


int main() 
{
    clock_t t;
    t = clock();
    printf("%ld\n", p182());
    t = clock()-t;
    printf("Time: %.3f\n", ((float) t)/CLOCKS_PER_SEC);
}