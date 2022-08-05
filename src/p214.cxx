#include <cstdio>
#include <ctime>

/*

Use a sieve to calculate totients, like in Problem 69, and then replace old
values with the chain length.

ANSWER 1677366278943

*/

long p214()
{
    const int size = 40000000;
    const int target = 25;
    long S = 0;

    // initialize array
    int *sieve = new int[size];
    for (int i = 0; i < size; i++)
        sieve[i] = i;

    // sieve
    int tot;
    for (int i = 2; i < size; i++)
    {
        tot = sieve[i];
        if (i == tot)
        { // is prime
            tot--;
            // multiply further totients
            for (int j = i; j < size; j += i)
                sieve[j] = (sieve[j] / i) * (i - 1);
            // check chain length
            if (sieve[tot] + 1 == target)
                S += i;
        }
        // replace sieve value with chain length
        sieve[i] = sieve[tot] + 1;
    }

    return S;
}

int main()
{
    clock_t t;
    t = clock();
    printf("%ld\n", p214());
    t = clock() - t;
    printf("Time: %.3f\n", ((float)t) / CLOCKS_PER_SEC);
}
