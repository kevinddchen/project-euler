#include <array>

/*

Use dynamic programming. We keep an array of the mdrs's of all integers up to
n. To calculate the mdrs of n, we iterate over all factors of n = a * b. We
have candidate drs's given by mdrs(a) + mdrs(b). We take the maximum of these
and store it in mdrs(n).

ANSWER 14489159

*/

int digital_root(int n)
{
    if (n < 10) {
        return n;
    }
    return 1 + (n - 1) % 9;
}

long p159()
{
    const int size = 1'000'000;

    std::array<int, size> mdrs;

    for (int n = 0; n < size; n++) {
        mdrs[n] = digital_root(n);
        // iterate over factors of n
        for (int factor = 2; factor * factor <= n; ++factor) {
            if (n % factor != 0) {
                continue;
            }
            const int drs = mdrs[factor] + mdrs[n / factor];
            if (drs > mdrs[n]) {
                mdrs[n] = drs;
            }
        }
    }

    // return sum for 1 < n < 1'000'000
    long sum = 0;
    for (int n = 2; n < size; n++) {
        sum += mdrs[n];
    }
    return sum;
}

int main()
{
    printf("%ld\n", p159());
}
