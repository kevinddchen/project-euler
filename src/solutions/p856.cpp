#include <mf/mathfuncs.hpp>

#include <vector>

/*

We can model the problem as a Markov chain. The state of the chain can be
described by:

- number of ranks where 0 cards have been drawn so far,
- number of ranks where 1 card has been drawn so far,
- number of ranks where 2 cards have been drawn so far,
- number of ranks where 3 cards have been drawn so far,
- number of ranks where all (4 cards) have been drawn so far,
- and n, where the most recently drawn card was the nth card drawn from that rank.

The total number of states is 5 * 14^5 = 2,689,120 and the chain always
terminates after at most 52 steps, so it is feasible to track the probabilities
of each state.

The transition probabilities are summarized in the `prob_*()` methods below.

ANSWER: 17.09661501

*/

constexpr int SUITS = 4;
constexpr int RANKS = 13;
constexpr int CARDS = SUITS * RANKS;

/**
 * State describing cards drawn so far.
 */
struct State {
    // The most recently drawn card was the `recent`th card drawn from that rank. Value 0 - 4.
    int recent;
    // Number of ranks where 0 cards have been drawn so far. Value 0 - 13.
    int rank_0;
    // Number of ranks where 1 card has been drawn so far. Value 0 - 13.
    int rank_1;
    // Number of ranks where 2 cards have been drawn so far. Value 0 - 13.
    int rank_2;
    // Number of ranks where 3 cards have been drawn so far. Value 0 - 13.
    int rank_3;
    // Number of ranks where all (4 cards) have been drawn so far. Value 0 - 13.
    int rank_4;

    /**
     * Total number of states.
     */
    static constexpr int num_states() { return S * R * R * R * R * R; }

    /**
     * Unique index of this state.
     */
    int to_index() const { return recent + S * (rank_0 + R * (rank_1 + R * (rank_2 + R * (rank_3 + R * rank_4)))); }

    /**
     * Total number of cards drawn so far.
     */
    int num_drawn() const { return rank_1 + 2 * rank_2 + 3 * rank_3 + 4 * rank_4; }

    /**
     * Probability of winning from this state.
     */
    double prob_win() const
    {
        if (recent == 1) {
            return 3.0 / (CARDS - num_drawn());
        } else if (recent == 2) {
            return 2.0 / (CARDS - num_drawn());
        } else if (recent == 3) {
            return 1.0 / (CARDS - num_drawn());
        } else {
            return 0.0;
        }
    }

    /**
     * Probability of drawing a card from the `rank_0` group.
     */
    std::pair<double, State> prob_0() const
    {
        const double prob = rank_0 * 4.0 / (CARDS - num_drawn());
        State copy = *this;
        copy.recent = 1;
        --copy.rank_0;
        ++copy.rank_1;

        return {prob, copy};
    }

    /**
     * Probability of drawing a card from the `rank_1` group.
     */
    std::pair<double, State> prob_1() const
    {
        const int available = recent == 1 ? rank_1 - 1 : rank_1;
        const double prob = available * 3.0 / (CARDS - num_drawn());
        State copy = *this;
        copy.recent = 2;
        --copy.rank_1;
        ++copy.rank_2;

        return {prob, copy};
    }

    /**
     * Probability of drawing a card from the `rank_2` group.
     */
    std::pair<double, State> prob_2() const
    {
        const int available = recent == 2 ? rank_2 - 1 : rank_2;
        const double prob = available * 2.0 / (CARDS - num_drawn());
        State copy = *this;
        copy.recent = 3;
        --copy.rank_2;
        ++copy.rank_3;

        return {prob, copy};
    }

    /**
     * Probability of drawing a card from the `rank_3` group.
     */
    std::pair<double, State> prob_3() const
    {
        const int available = recent == 3 ? rank_3 - 1 : rank_3;
        const double prob = available * 1.0 / (CARDS - num_drawn());
        State copy = *this;
        copy.recent = 4;
        --copy.rank_3;
        ++copy.rank_4;

        return {prob, copy};
    }

private:
    // Total number of rank states, i.e. 0 - 13.
    static constexpr int R = RANKS + 1;
    // Total number of recent states, i.e. 0 - 4.
    static constexpr int S = SUITS + 1;
};

double p856()
{
    // Initialize state probabilities.
    const int num_states = State::num_states();
    std::vector<double> probs(num_states, 0.0);

    // Initialize the first state.
    State s = {0, 13, 0, 0, 0, 0};
    probs[s.to_index()] = 1.0;

    std::vector<State> prev_states;
    prev_states.push_back(std::move(s));

    // Draw cards and accumulate expected value.
    double ev = 0.0;
    for (int num_drawn = 1; num_drawn <= 52; ++num_drawn) {
        std::vector<State> states;

        // Iterate over next states.
        for (const auto& prev_state : prev_states) {
            const double prob = probs[prev_state.to_index()];

            // Probability to win.
            const double prob_win = prob * prev_state.prob_win();
            ev += prob_win * num_drawn;

            // Update the probabilities for the next states.
            std::vector<std::pair<double, State>> new_prob_states;
            new_prob_states.push_back(prev_state.prob_0());
            new_prob_states.push_back(prev_state.prob_1());
            new_prob_states.push_back(prev_state.prob_2());
            new_prob_states.push_back(prev_state.prob_3());
            for (const auto& [new_prob, new_state] : new_prob_states) {
                if (new_prob == 0.0) {
                    continue;
                }
                if (probs[new_state.to_index()] == 0.0) {
                    states.push_back(new_state);
                }
                probs[new_state.to_index()] += prob * new_prob;
            }
        }
        prev_states = std::move(states);
    }

    // If cards are drawn until the end, that counts as 52 cards drawn.
    const State end = {4, 0, 0, 0, 0, 13};
    ev += probs[end.to_index()] * 52;

    return ev;
}

int main()
{
    printf("%.8f\n", mf::round(p856(), 8));
}
