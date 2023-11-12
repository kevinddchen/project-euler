#include "common.h"

#include <vector>

/*

Use a sieve to calculate totients, like in Problem 69, and then replace old
values with the chain length.

ANSWER 1677366278943

*/

long p214()
{
    const int size = 40'000'000;
    const int target = 25;
    long sum = 0;

    // initialize array
    std::vector<int> sieve(size);
    for (int i = 0; i < size; i++) {
        sieve[i] = i;
    }

    // sieve
    int tot;
    for (int i = 2; i < size; i++) {
        tot = sieve[i];
        if (i == tot) {  // is prime
            tot--;
            // multiply further totients
            for (int j = i; j < size; j += i) {
                sieve[j] = (sieve[j] / i) * (i - 1);
            }
            // check chain length
            if (sieve[tot] + 1 == target) {
                sum += i;
            }
        }
        // replace sieve value with chain length
        sieve[i] = sieve[tot] + 1;
    }

    return sum;
}

int main()
{
    TIMED(printf("%ld\n", p214()));
}
