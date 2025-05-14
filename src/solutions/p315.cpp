#include <mf/mathfuncs.hpp>

#include <array>

/*

Brute force.

ANSWER 13625242

*/

template <size_t n_digits>
struct Clock {
    int n;
    std::array<int, n_digits> digit_states;

    Clock(int n) : n(n)
    {
        for (int i = 0; i < n_digits; i++) {
            if (n == 0) {
                digit_states[i] = 10;
            } else {
                digit_states[i] = n % 10;
            }
            n /= 10;
        }
    }
};

int digital_root(int x)
{
    if (x < 10) {
        return 0;
    }
    int root = 0;
    while (x != 0) {
        root += x % 10;
        x /= 10;
    }
    return root;
}

template <size_t n_digits>
int count_on(const Clock<n_digits>& clock1, const Clock<n_digits>& clock2, const bool light_segments[11][7])
{
    int count = 0;
    for (int i = 0; i < n_digits; i++) {
        const auto& states1 = light_segments[clock1.digit_states[i]];
        const auto& states2 = light_segments[clock2.digit_states[i]];
        for (int segm = 0; segm < 7; segm++) {
            if (states1[segm] && states2[segm]) {
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
    const bool light_segments[11][7] = {
        {1, 1, 1, 0, 1, 1, 1},  // 0
        {0, 0, 1, 0, 0, 1, 0},  // 1
        {1, 0, 1, 1, 1, 0, 1},  // 2
        {1, 0, 1, 1, 0, 1, 1},  // 3
        {0, 1, 1, 1, 0, 1, 0},  // 4
        {1, 1, 0, 1, 0, 1, 1},  // 5
        {1, 1, 0, 1, 1, 1, 1},  // 6
        {1, 1, 1, 0, 0, 1, 0},  // 7
        {1, 1, 1, 1, 1, 1, 1},  // 8
        {1, 1, 1, 1, 0, 1, 1},  // 9
        {0, 0, 0, 0, 0, 0, 0}   // (empty)
    };

    // count transitions
    long count = 0;

    const auto sieve = mf::prime_sieve(limit);
    for (int i = limit / 2; i < limit; i++) {
        if (!sieve[i]) {
            continue;
        }

        Clock<n_digits> A(i);
        int j = digital_root(i);

        while (j > 0) {
            Clock<n_digits> B(j);
            count += 2 * count_on<n_digits>(A, B, light_segments);
            A = B;
            j = digital_root(j);
        }
    }
    return count;
}

int main()
{
    printf("%ld\n", p315());
}
