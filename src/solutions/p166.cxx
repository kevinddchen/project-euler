#include "common.h"

#include <algorithm>

/*

Brute force. Even though the grid has 16 parameters, only 9 are actually
independent. If we write the grid as

a b c d
e f g h
i j k l
m n o p

given a, b, c, and d we know the sum for each row. Thus if we also know e, f,
g, i, and k we can deduce all the other numbers.

ANSWER 7130034

*/

long p166()
{
    int count = 0;

    for (int a = 0; a < 10; a++) {
        for (int b = 0; b < 10; b++) {
            for (int c = 0; c < 10; c++) {
                for (int d = 0; d < 10; d++) {
                    const int sum = a + b + c + d;
                    for (int e = 0; e < 10; e++) {
                        const int imin = std::max(0, sum - a - e - 9);
                        const int imax = std::min(9, sum - a - e);
                        for (int i = imin; i <= imax; i++) {
                            const int m = sum - a - e - i;
                            assert(m >= 0 && m <= 9);

                            const int gmin = std::max(0, sum - d - m - 9);
                            const int gmax = std::min(9, sum - d - m);
                            for (int g = gmin; g <= gmax; g++) {
                                const int j = sum - d - m - g;
                                assert(j >= 0 && j <= 9);

                                const int fmin = std::max(std::max(0, sum - e - g - 9), sum - b - j - 9);
                                const int fmax = std::min(std::min(9, sum - e - g), sum - b - j);
                                for (int f = fmin; f <= fmax; f++) {
                                    const int h = sum - e - g - f;
                                    assert(h >= 0 && h <= 9);
                                    const int n = sum - b - j - f;
                                    assert(n >= 0 && n <= 9);

                                    const int kmin = std::max(
                                        std::max(std::max(0, sum - i - j - 9), sum - c - g - 9), sum - a - f - 9);
                                    const int kmax =
                                        std::min(std::min(std::min(9, sum - i - j), sum - c - g), sum - a - f);
                                    for (int k = kmin; k <= kmax; k++) {
                                        const int l = sum - i - j - k;
                                        assert(l >= 0 && l <= 9);
                                        const int o = sum - c - g - k;
                                        assert(o >= 0 && o <= 9);
                                        const int p = sum - a - f - k;
                                        assert(p >= 0 && p <= 9);

                                        // final check that is not guaranteed by the constraints
                                        if (d + h + l + p == sum && m + n + o + p == sum) {
                                            count++;
                                        }
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
    TIMED(printf("%ld\n", p166()));
}
