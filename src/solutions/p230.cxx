#include "common.h"
#include "mathfuncs.h"

#include <string>
#include <vector>

/*

For a given A and B, we note that if F_i(n) denotes the nth digit of the ith
element of the sequence F_{A,B}, then we have the following recursion relation:

    let L_i = length of the ith element of F_{A,B}
    F_i(n) = F_{i-2}(n) if n <= L
           = F_{i-1}(n-L)
    F_1(n) = nth digit of A
    F_2(n) = nth digit of B

All that remains is to compute L_i until we exceed the desired initial n.

ANSWER

*/

int get_nth_digit(const std::string& A, const std::string& B, long n)
{
    // first, compute length of each string in the sequence F_{A,B} until we exceed n
    std::vector<long> lengths = {(long)A.length(), (long)B.length()};
    while (lengths.back() < n) {
        const auto size = lengths.size();
        lengths.push_back(lengths[size - 2] + lengths[size - 1]);
    }

    // second, use recursive formula to determine digit of A or B
    long index = lengths.size() - 1;
    while (index > 1) {
        // compare n to length of the i-2 term
        const auto length_front = lengths[index - 2];
        if (n <= length_front) {
            index -= 2;
        } else {
            n -= length_front;
            index -= 1;
        }
    }

    char d;
    if (index == 0) {
        d = A[n - 1];
    } else {
        d = B[n - 1];
    }

    // return numerical value of character
    return d - '0';
}

long p0()
{
    const std::string A =
        "1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679";
    const std::string B =
        "8214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196";

    long answer = 0;
    for (long n = 0; n <= 17; ++n) {
        const auto digit = get_nth_digit(A, B, (127 + 19 * n) * mf::pow(7, n));
        answer += mf::pow(10, n) * digit;
    }

    return answer;
}

int main()
{
    printf("%ld\n", p0());
}
