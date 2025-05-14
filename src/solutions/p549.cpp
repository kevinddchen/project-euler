#include <vector>

/*

Note that s(n) can be calculated from its prime factorization. If
n = p1^a1 * p2^a2 * ... * pk^ak, then

    s(n) = MAX{ s(p1^a1), s(p2^a2), ... , s(pk^ak) }

We use a sieve to keep track of s(n), and go through all powers of all primes.

ANSWER 476001479068717

*/

/* Count number of times d divides into x. */
int count_divisions(int x, int d)
{
    int c = 0;
    while (x % d == 0) {
        x /= d;
        c++;
    }
    return c;
}

long p549()
{
    const int size = 100'000'000;
    long sum = 0;

    std::vector<int> s(size + 1);

    for (int p = 2; p <= size; p++) {
        if (s[p] != 0)  // if not prime
        {
            sum += s[p];
            continue;
        }
        sum += p;  // if prime, then s[p] = p

        int s_n = p;
        int a_to_add = 1;  // used for calculating s(p_power)
        long p_power = p;
        while (p_power <= size)  // iterate through powers of p
        {
            // calculate s(p_power)
            // e.g. s(2) = 2, s(4) = s(8) = 4, s(16) = 6, ...
            if (a_to_add == 0) {
                s_n += p;
                a_to_add = count_divisions(s_n, p);
            }
            a_to_add--;
            // set s(n) for all multiples of p_power
            int j;
            for (j = p_power; j <= size; j += p_power) {
                if (s_n > s[j]) {
                    s[j] = s_n;
                }
            }
            // next power of p
            p_power *= p;  // (p_power is long to prevent overflow in this step)
        }
    }

    return sum;
}

int main()
{
    printf("%ld\n", p549());
}
