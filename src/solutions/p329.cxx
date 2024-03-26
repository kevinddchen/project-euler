#include "common.h"
#include "containers.h"
#include "mathfuncs.h"

#include <array>
#include <string>

/*

We use Markov chains to keep a track of the probabilities for each square.
Starting with initial probabilities of 1/500 for each square, a "croak" is
handled by multiplying the probabilities by 1/3 or 2/3, depending on the letter
croaked and the value on the square, and a "jump" is handled by updating the
probabilities based on the probabilities of the adjacent squares.

ANSWER 199740353/29386561536000

*/

static const int SIZE = 500;

/**
 * Update probabilities due to frog croaking the given letter.
 */
void croak(std::array<mf::Frac, SIZE>& probs, const std::vector<bool>& prime_sieve, char letter)
{
    for (int i = 0; i < SIZE; ++i) {
        const int n = i + 1;  // number written on the square
        if (letter == 'P') {
            probs[i] = probs[i] * (prime_sieve[n] ? mf::Frac(2, 3) : mf::Frac(1, 3));
        } else {
            probs[i] = probs[i] * (prime_sieve[n] ? mf::Frac(1, 3) : mf::Frac(2, 3));
        }
    }
}

/**
 * Update probabilities due to frog jumping.
 */
void jump(std::array<mf::Frac, SIZE>& probs)
{
    std::array<mf::Frac, SIZE> new_probs;

    // handle special cases at the ends
    new_probs[0] = probs[1] * mf::Frac(1, 2);
    new_probs[1] = probs[0] + probs[2] * mf::Frac(1, 2);
    new_probs[SIZE - 2] = probs[SIZE - 3] * mf::Frac(1, 2) + probs[SIZE - 1];
    new_probs[SIZE - 1] = probs[SIZE - 2] * mf::Frac(1, 2);

    for (int i = 2; i < SIZE - 2; ++i) {
        new_probs[i] = probs[i - 1] * mf::Frac(1, 2) + probs[i + 1] * mf::Frac(1, 2);
    }

    probs = new_probs;
}

mf::Frac p329()
{
    const std::string sequence = "PPPPNNPPPNPPNPN";

    // generate prime sieve
    const std::vector<bool> sieve = mf::prime_sieve(SIZE + 1);

    // initialize probabilities
    std::array<mf::Frac, SIZE> probs;
    probs.fill(mf::Frac(1, SIZE));

    for (int i = 0; i < sequence.length(); ++i) {
        croak(probs, sieve, sequence[i]);
        jump(probs);
    }

    mf::Frac sum = std::accumulate(probs.begin(), probs.end(), mf::Frac(0));
    return sum;
}

int main()
{
    const auto ans = p329();
    printf("%ld/%ld\n", ans.numer, ans.denom);
}
