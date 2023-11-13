#include "common.h"
#include "mathfuncs.h"

#include <queue>

/*

We start from 2 and recursively generate all connected primes. For reasons that
we will explain shortly, these primes are traversed in increasing order using a
priority queue. So the first few primes we encounter will be 2, 3, 5, 7, 13,
11, ...

For each new prime `p` we encounter, we keep track of the maximum prime in the
chain to 2, called `connected[p]`. But since we are encountering the primes `p`
in increasing order, we can be sure that `connected[p]` is the smallest out of
all possible chains (otherwise, we would have encountered `p` earlier).

ANSWER 46479497324

*/

long p425()
{
    const int limit = 10'000'000;

    // pre-compute primes
    const auto prime_sieve = mf::prime_sieve(limit + 1);

    // array keeping track of maximum prime in the chain to 2; -1 means not connected yet
    std::vector<int> connected(limit + 1, -1);
    connected[2] = 2;

    // priority queue of primes yet to process
    std::priority_queue<int, std::vector<int>, std::greater<int>> queue;
    queue.push(2);

    // update data structures given possible connection x -> y
    auto update = [&](int x, int y) {
        if (y > limit || !prime_sieve[y]) {
            return;
        }

        const int new_connected_y = std::max(connected[x], y);
        if (connected[y] < 0) {  // not connected yet; make new chain
            connected[y] = new_connected_y;
            queue.push(y);
        } else {  // already connected; check that new chain has larger maximum
            assert(connected[y] <= new_connected_y);
        }
    };

    // generate over all connected primes
    while (!queue.empty()) {
        const int x = queue.top();
        queue.pop();

        // iterate over all place values
        int place_value = 1;
        while (place_value <= x) {
            const int digit = (x / place_value) % 10;
            // replace digit
            for (int new_digit = 0; new_digit < 10; new_digit++) {
                if (new_digit == digit) {
                    continue;
                }
                const int y = x + (new_digit - digit) * place_value;
                update(x, y);
            }
            place_value *= 10;
        }

        // append a digit on the left
        for (int new_digit = 1; new_digit < 10; new_digit++) {
            const int y = x + new_digit * place_value;
            update(x, y);
        }
    }

    // sum over all primes not connected or are connected to 2 but the maximum prime in the chain is larger than itself
    long sum = 0;
    for (int p = 3; p <= limit; p += 2) {
        if (prime_sieve[p] && (connected[p] < 0 || connected[p] > p)) {
            sum += p;
        }
    }

    return sum;
}

int main()
{
    TIMED(printf("%ld\n", p425()));
}
