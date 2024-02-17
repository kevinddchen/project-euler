#include "common.h"

#include <array>

/*

Brute force. Iterate over all occurrences of digits, e.g. 0 appears a0 times, 1
appears a1 times, ... Given an [a0, a1, ..., a9] that adds up to 18,  we count
the possible combinations of digits, making sure that the leading digit is not
0.

My specific implementation is very ugly with many nested loops, but it was
fast to write.

ANSWER 227485267000992000

*/

static const int DIGITS = 18;

long p0()
{
    // Generate Pascal's triangle to calculate up to `18 choose k`
    std::array<std::array<long, DIGITS + 1>, DIGITS + 1> choose;
    for (int i = 0; i <= DIGITS; ++i) {
        choose[i][0] = 1;
        choose[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            choose[i][j] = choose[i - 1][j - 1] + choose[i - 1][j];
        }
    }

    // Iterate over all digit occurrences
    // ai = occurrences of digit i
    // ni = number of remaining digits to choose from

    long count = 0;

    for (int a0 = 0; a0 <= 3; ++a0) {
        const int n0 = 17;  // cannot have leading zero
        for (int a1 = 0; a1 <= 3; ++a1) {
            const int n1 = n0 + 1 - a0;  // +1 as this digit can be the leading digit
            for (int a2 = 0; a2 <= 3; ++a2) {
                const int n2 = n1 - a1;
                for (int a3 = 0; a3 <= 3; ++a3) {
                    const int n3 = n2 - a2;
                    for (int a4 = 0; a4 <= 3; ++a4) {
                        const int n4 = n3 - a3;
                        for (int a5 = 0; a5 <= 3; ++a5) {
                            const int n5 = n4 - a4;
                            for (int a6 = 0; a6 <= 3; ++a6) {
                                const int n6 = n5 - a5;
                                for (int a7 = 0; a7 <= 3; ++a7) {
                                    const int n7 = n6 - a6;
                                    for (int a8 = 0; a8 <= 3; ++a8) {
                                        const int n8 = n7 - a7;
                                        const int n9 = n8 - a8;
                                        const int a9 = n9;
                                        if (a9 < 0 || a9 > 3) {
                                            continue;
                                        }

                                        count += choose[n0][a0] * choose[n1][a1] * choose[n2][a2] * choose[n3][a3] *
                                                 choose[n4][a4] * choose[n5][a5] * choose[n6][a6] * choose[n7][a7] *
                                                 choose[n8][a8] * choose[n9][a9];
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return count;
}

int main()
{
    printf("%ld\n", p0());
}
