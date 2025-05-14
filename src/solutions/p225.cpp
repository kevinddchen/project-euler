#include <algorithm>

/*

Brute force. For each odd n, we check the tribonacci numbers mod n. Such a
sequence must be periodic. Moreover, because the tribonacci sequence can be
defined backwards as well as forwards, we will eventually reach the initial
state (1, 1, 1) again.

ANSWER 2009

*/

/**
 * Check if an odd number divides some tribonacci number.
 */
bool check_divisibility(long n)
{
    long a = 1;
    long b = 1;
    long c = 1;

    while (true) {
        c = (a + b + c) % n;
        std::swap(b, c);
        std::swap(a, b);

        if (a == 0) {
            return true;
        } else if (a == 1 && b == 1 && c == 1) {
            return false;
        }
    }
}

long p225()
{
    const int target = 124;

    int count = 0;
    for (long n = 3;; n += 2) {
        if (!check_divisibility(n)) {
            count++;
            if (count == target) {
                return n;
            }
        }
    }
}

int main()
{
    printf("%ld\n", p225());
}
