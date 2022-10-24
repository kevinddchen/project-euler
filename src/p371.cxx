#include "common.h"
#include "mathfuncs.h"

#include <array>
#include <vector>

/*

At any given moment in time, the state is parametrized by two values: the
number of targets t that will allow a win, and a boolean flag whether or not
500 has been seen.

For each new license plate, we have a transition probability between states, as
well as a probability to "win". We then just calcualte the expected time to
"win".

ANSWER

*/

constexpr int TOTAL = 1000;
constexpr int T_STATES = 501;


struct Probs {
    std::array<double, T_STATES> yes_500;
    std::array<double, T_STATES> no_500;

    Probs()
    {
        for (int t = 0; t < no_500.size(); t++) {
            no_500[t] = 0.0;
            yes_500[t] = 0.0;
        }
    }
};


double p371()
{
    // numerical tolerance--set below 1e-8
    constexpr double TOLERANCE = 1e-12;

    // initialize probabilities
    Probs p;
    p.no_500[0] = 1.0;

    double ev = 0.0;

    int num_plates = 0;
    double sum_probs = 1.0;  // sum of values in p

    while (num_plates == 0 || num_plates * sum_probs > TOLERANCE) {
        num_plates++;
        sum_probs = 0.0;
        double prob_win = 0.0;

        Probs new_p;

        // for no 500, max t is 499
        for (int t = 0; t < T_STATES - 1; t++) {
            // chance of winning
            prob_win += p.no_500[t] * t / TOTAL;
            sum_probs += p.no_500[t] * (TOTAL - t) / TOTAL;
            // chance of seeing 000 or a previously seen plate
            new_p.no_500[t] += p.no_500[t] * (t + 1) / TOTAL;
            // chance of seeing 500
            new_p.yes_500[t + 1] += p.no_500[t] / TOTAL;
            // chance of seeing a new plate (except 000 or 500) and not winning
            new_p.no_500[t + 1] += p.no_500[t] * (TOTAL - 2 * t - 2) / TOTAL;
        }
        // for yes 500, min t is 1
        for (int t = 1; t < T_STATES; t++) {
            // chance of winning
            prob_win += p.yes_500[t] * t / TOTAL;
            sum_probs += p.yes_500[t] * (TOTAL - t) / TOTAL;
            // chance of seeing 000 or a previously seen plate (except 500)
            new_p.yes_500[t] += p.yes_500[t] * t / TOTAL;
            // chance of seeing a new plate (except 000) and not winning
            if (t < T_STATES - 1) {
                new_p.yes_500[t + 1] += p.yes_500[t] * (TOTAL - 2 * t) / TOTAL;
            }
        }

        // update expected value and probabilities
        ev += prob_win * num_plates;
        p = new_p;
    }

    return ev;
}

int main()
{
    TIMED(printf("%.8f\n", mf::round(p371(), 8)));
}
