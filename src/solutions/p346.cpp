#include <set>

/*

Brute force. Note that any number n is 11 in base n-1. With this in mind, we
just enumerate all numbers for all bases up to 10^6, checking for repeats.

ANSWER 336108797689259276

*/

long p346()
{
    const long limit = 1'000'000'000'000;
    long sum = 1;

    std::set<long> repeats;

    for (long i = 2; i * i < limit; i++) {
        long x = (i + 1) * i + 1;
        while (x < limit) {
            auto it = repeats.find(x);
            if (it == repeats.end())  // if x has not been encountered yet
            {
                sum += x;
                repeats.insert(x);
            }
            x = x * i + 1;
        }
    }
    return sum;
}

int main()
{
    printf("%ld\n", p346());
}
