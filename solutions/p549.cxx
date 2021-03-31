// p549.cxx
#include <stdio.h>
#include <iostream>
#include <map>
#include <vector>
#include <math.h>
#include <time.h>
#include "cmathfuncs.h"
using namespace std;


/*

Brute force. Runs in over 1 min. It is important to notice that s(n) can be
calculated on its prime factorization quite easily.

    n = (p_1)^(k_1) * (p_2)^(k_2) * ... * (p_n)^(k_n)

for distinct primes p_1, p_2, ..., p_n. Then,

    s(n) = MAX{ s( p_1^k_1 ), s(p_2^k_2), ... , s(p_n^k_n) }

Then used sieves to quickly calculate prime factorizations.

ANSWER 476001479068717

*/



int count_divisions(int x, int d){
    /* Returns number of times d divides into x evenly. */
    int c = 0;
    while (x%d == 0) {
        x /= d;
        c++;
    }
    return c;
}



unsigned short * factorSieve(long int size) {
    /* Create prime sieve of smallest prime factor. */
    unsigned short * sieve = new unsigned short[size+1]();
    sieve[0] = sieve[1] = 1;
    for (long int i=2; i<= size; i++) {
        if (sieve[i]==0) {
            for (long int j=i*i; j<=size; j+=i) {
                if (sieve[j] == 0)
                    sieve[j] = i;
            }
        }
    }
    return sieve;
}



map<long int, long int> powerTable(long int size, unsigned short * sieve) {
    /* Create table counting divisibility of powers of primes. */
    map<long int, long int> table;
    for (long int i=2; i<=size; i++) {
        if (sieve[i] == 0) {
            long int    val = i, fact_val = i;
            int         exp = 1, fact_exp = 1;

            while (val <= size) {
                if (exp > fact_exp) {
                    fact_val += i;
                    fact_exp += count_divisions(fact_val, i);
                }
                table[val] = fact_val;
                val *= i;
                exp++;
            }
        }
    }
    return table;
}



vector<long int> primeSieveFactorize(long int x, unsigned short * sieve) {
    vector<long int> facts;
    while (sieve[x] >= 2) {
        int i = sieve[x];
        int c = 0;
        while (sieve[x] == i or x==i) {
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



long int p549() {

    long int size = 100000000;
    
    // prepare prime sieve
    unsigned short * sieve = factorSieve(size);

    // prepare power table
    map<long int, long int> table = powerTable(size, sieve);   

    // calculate sum
    long long int S = 0;

    vector<long int> facts;
    vector<long int>::iterator v;
    long int M, x;

    for (long int i=2; i<=size; i++) {
        facts = primeSieveFactorize(i, sieve);
        v = facts.begin();
        M = 0;

        while (v != facts.end()) {
            x = table[pow(*(v++), *(v++))];
            if (x > M)
                M = x;
        }

        S += M;

    }
    return S;
}

int main() {
    clock_t t;
    t = clock();
    printf("%ld\n", p549());
    t = clock()-t;
    printf("Time: %.3f\n", ((float) t)/CLOCKS_PER_SEC);
}
