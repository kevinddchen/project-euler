#include <cstdio>
#include <ctime>
#include "mathfuncs.h"


/*

Brute force.

ANSWER 13625242

*/


int digital_root(int x) 
{
    if (x < 10)
        return 0;
    int root = 0;
    while (x != 0) 
    {
        root += x%10;
        x /= 10;
    }
    return root;
}


bool ** clock(int n, bool digits[11][7]) 
{
    bool ** clock = new bool * [8];
    for (int i=0; i<8; i++) 
    {
        if (n == 0)
            clock[i] = digits[10];
        else
            clock[i] = digits[n%10];
        n /= 10;
    }
    return clock;
}


int count_on(bool ** clock1, bool ** clock2) 
{
    int c = 0;
    for (int i=0; i<8; i++) 
    {
        for (int j=0; j<7; j++) 
        {
            if (clock1[i][j] and clock2[i][j])
                c++;
        }
    }
    return c;
}


long p315() 
{
    // for each digit, which lights are on
    bool digits[11][7] = {
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
        {0, 0, 0, 0, 0, 0, 0}   
    };

    // count transitions
    long c = 0;
    bool * sieve = prime_sieve(20000000);
    for (int i=10000000; i<20000000; i++) 
    {
        if (!sieve[i])
            continue;

        bool ** A = clock(i, digits);
        int j = digital_root(i);

        while (j > 0) 
        {
            bool ** B = clock(j, digits);
            c += 2 * count_on(A, B);
            A = B;
            j = digital_root(j);
        }
    }
    return c;
}


int main() 
{
    clock_t t;
    t = clock();
    printf("%ld\n", p315());
    t = clock()-t;
    printf("Time: %.3f\n", ((float) t)/CLOCKS_PER_SEC);
}
