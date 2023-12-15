#include "common.h"
#include "mathfuncs.h"

#include <array>

/*

We iterate through all combinations of digits. For each combination, we go
through its power sums for k = 1, 2, 3, ... and check if the power sum +/- 1
contains the same digits. If so, we have a near power sum.

ANSWER 13459471903176422

*/

static const int BASE = 10;

/**
 * Get digit representation of an integer, i.e. array containing number of 0s,
 * 1s, 2s, ...,  9s.
 */
std::array<int, BASE> digits_from_num(long num)
{
    assert(num >= 0);
    std::array<int, BASE> digits = {0};
    while (num > 0) {
        digits[num % BASE]++;
        num /= BASE;
    }
    return digits;
}

/**
 * Check if two arrays of digits are equal, ignoring zeros.
 */
bool digits_equal(const std::array<int, BASE>& digits1, const std::array<int, BASE>& digits2)
{
    // skip 0
    for (int i = 1; i < BASE; i++) {
        if (digits1[i] != digits2[i]) {
            return false;
        }
    }
    return true;
}

/**
 * Returns true if all digits are 0 or 1.
 */
bool digits_all_zeros_or_ones(const std::array<int, BASE>& digits)
{
    for (int i = 2; i < BASE; i++) {
        if (digits[i] != 0) {
            return false;
        }
    }
    return true;
}

/**
 * Compute sum of digits raised to `power`.
 */
long compute_power_sum(const std::array<int, BASE>& digits, int power)
{
    assert(power > 0);
    long sum = 0;
    // skip 0, since their powers are always 0 for power > 0
    for (int i = 1; i < BASE; i++) {
        sum += digits[i] * mf::pow(i, power);
    }
    return sum;
}

/**
 * Check if a given set of digits corresponds to a near power sum. If so,
 * returns true and sets `near_power_sum` to the near power sum. Otherwise,
 * returns false.
 */
bool is_near_power_sum(const std::array<int, BASE>& digits, long limit, long& near_power_sum)
{
    // if digits only contain 0s and 1s, then can never be near power sum
    if (digits_all_zeros_or_ones(digits)) {
        return false;
    }

    for (int power = 1; true; power++) {
        const long power_sum = compute_power_sum(digits, power);
        if (power_sum >= limit) {
            return false;
        }

        // try adding 1 or -1 to the sum, see if we get a number whose digits match
        for (int a : {1, -1}) {
            const long possible_near_power_sum = power_sum + a;
            const std::array<int, BASE> digits_near = digits_from_num(possible_near_power_sum);
            if (digits_equal(digits, digits_near)) {
                near_power_sum = possible_near_power_sum;
                return true;
            }
        }
    }
}

struct Node {
    std::array<int, BASE> digits;
    int current_index;
};

/**
 * Use depth-first search to traverse combinations of digits, and find near
 * power sums.
 */
long dfs(int num_digits)
{
    const long limit = mf::pow(10, num_digits);

    std::vector<Node> stack;
    stack.push_back({{0}, 0});
    stack.back().digits[0] = num_digits;  // start with all digits in 0s place

    long sum = 0;

    while (!stack.empty()) {
        const Node node = stack.back();
        stack.pop_back();

        // see if `node.digits` corresponds to a near power sum
        long near_power_sum;
        if (is_near_power_sum(node.digits, limit, near_power_sum)) {
            sum += near_power_sum;
        }

        if (node.current_index == BASE - 1) {
            continue;
        }

        // generate children
        // carry over at least one
        for (int carry = 1; carry <= node.digits[node.current_index]; carry++) {
            std::array<int, BASE> child_digits = node.digits;
            child_digits[node.current_index] -= carry;
            child_digits[node.current_index + 1] += carry;
            const Node child = {child_digits, node.current_index + 1};
            stack.push_back(child);
        }
    }
    return sum;
}

long p749()
{
    const int num_digits = 16;
    return dfs(num_digits);
}

int main()
{
    printf("%ld\n", p749());
}
