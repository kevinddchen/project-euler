#include <algorithm>
#include <unordered_map>
#include <vector>

#include <cassert>

/*

We iterate over all values of s^2 + c^3, and keep a dictionary tracking the
number of times we encounter each palindrome. Since we want the five smallest
of such palindromes, we iterate over all values where s^2 + c^3 < limit, where
limit is increased by a factor of 10 each iteration. This is implemented by
keeping track of the values of `s` that have already been computed for each
value of `c`.

ANSWER 1004195061

*/

bool is_palindrome(long n)
{
    // first, convert to digits
    std::vector<long> digits;
    while (n > 0) {
        digits.push_back(n % 10);
        n /= 10;
    }
    // second, compare digits
    for (int i = 0; i < static_cast<int>(digits.size()) / 2; ++i) {
        if (digits[i] != digits[digits.size() - i - 1]) {
            return false;
        }
    }
    return true;
}

long p348()
{
    constexpr long TARGET = 5;
    constexpr long INIT_LIMIT = 10'000'000;

    // keeps track of palindromes and their counts
    std::unordered_map<long, long> palindromes;

    // array to keep track of explored s for each c in s^2 + c^3
    std::vector<long> cube_bases = {-1, -1};  // dummy values for 0 and 1

    for (long limit = INIT_LIMIT;; limit *= 10) {
        // generate new palindromes up to `limit`
        for (long cube_base = 2;; ++cube_base) {
            const long cube = cube_base * cube_base * cube_base;
            if (cube >= limit) {
                break;
            }

            // make sure that `cube_bases[cube_base]` exists
            while (cube_base >= static_cast<int>(cube_bases.size())) {
                cube_bases.push_back(2);
            }
            assert(cube_base < static_cast<int>(cube_bases.size()));

            for (long& square_base = cube_bases[cube_base];; square_base++) {
                const long num = cube + square_base * square_base;
                if (num >= limit) {
                    break;
                }

                if (is_palindrome(num)) {
                    // increment count if already encountered, otherwise add to dict
                    if (auto search = palindromes.find(num); search != palindromes.end()) {
                        ++(search->second);
                    } else {
                        palindromes.insert(std::make_pair(num, 1));
                    }
                }
            }
        }

        // get palindromes with exactly 4 counts
        std::vector<long> target_palindromes;
        for (const auto [num, count] : palindromes) {
            if (count == 4) {
                target_palindromes.push_back(num);
            }
        }

        // if enough palindromes, sort and return sum of smallest 5
        if (target_palindromes.size() >= TARGET) {
            std::sort(target_palindromes.begin(), target_palindromes.end());

            long sum = 0;
            for (int i = 0; i < TARGET; ++i) {
                sum += target_palindromes[i];
            }
            return sum;
        }
    }
    throw std::runtime_error("Unreachable code.");
}

int main()
{
    printf("%ld\n", p348());
}
