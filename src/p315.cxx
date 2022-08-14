#include "common.h"
#include "mathfuncs.h"

/*

Brute force.

ANSWER 13625242

*/

int digital_root(int x)
{
    if (x < 10)
    {
        return 0;
    }
    int root = 0;
    while (x != 0)
    {
        root += x % 10;
        x /= 10;
    }
    return root;
}

bool **clock(int n, bool light_segments[11][7], int n_digits)
{
    bool **clock = new bool *[n_digits];
    for (int i = 0; i < n_digits; i++)
    {
        if (n == 0)
        {
            clock[i] = light_segments[10];
        }
        else
        {
            clock[i] = light_segments[n % 10];
        }
        n /= 10;
    }
    return clock;
}

int count_on(bool **clock1, bool **clock2, int n_digits)
{
    int count = 0;
    for (int i = 0; i < n_digits; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (clock1[i][j] and clock2[i][j])
            {
                count++;
            }
        }
    }
    return count;
}

long p315()
{
    const long limit = 20'000'000;
    const int n_digits = 8;

    // for each digit, which lights are on
    bool light_segments[11][7] = {
        {1, 1, 1, 0, 1, 1, 1}, // 0
        {0, 0, 1, 0, 0, 1, 0}, // 1
        {1, 0, 1, 1, 1, 0, 1}, // 2
        {1, 0, 1, 1, 0, 1, 1}, // 3
        {0, 1, 1, 1, 0, 1, 0}, // 4
        {1, 1, 0, 1, 0, 1, 1}, // 5
        {1, 1, 0, 1, 1, 1, 1}, // 6
        {1, 1, 1, 0, 0, 1, 0}, // 7
        {1, 1, 1, 1, 1, 1, 1}, // 8
        {1, 1, 1, 1, 0, 1, 1}, // 9
        {0, 0, 0, 0, 0, 0, 0}  // (empty)
    };

    // count transitions
    long count = 0;

    PrimeSieve sieve(limit);
    for (int i = limit / 2; i < limit; i++)
    {
        if (!sieve[i])
        {
            continue;
        }

        bool **A = clock(i, light_segments, n_digits);
        int j = digital_root(i);

        while (j > 0)
        {
            bool **B = clock(j, light_segments, n_digits);
            count += 2 * count_on(A, B, n_digits);
            delete[] A;
            A = B;
            j = digital_root(j);
        }
        delete[] A;
    }
    return count;
}

int main()
{
    TIMED(printf("%ld\n", p315()));
}
