#include <Eigen/Dense>

#include <cassert>
#include <cmath>
#include <cstdio>


/*

It is best to first visualize the pattern of wins/losses for (a, b) on a grid. Below is shown for 31x31.

1010101010101010101010101010101
0010001000100010001000100010001
1110001000100010001000100010001
0000001000000010000000100000001
1000001000000010000000100000001
0000001000000010000000100000001
1111111000000010000000100000001
0000000000000010000000000000001
1000000000000010000000000000001
0000000000000010000000000000001
1110000000000010000000000000001
0000000000000010000000000000001
1000000000000010000000000000001
0000000000000010000000000000001
1111111111111110000000000000001
0000000000000000000000000000001
1000000000000000000000000000001
0000000000000000000000000000001
1110000000000000000000000000001
0000000000000000000000000000001
1000000000000000000000000000001
0000000000000000000000000000001
1111111000000000000000000000001
0000000000000000000000000000001
1000000000000000000000000000001
0000000000000000000000000000001
1110000000000000000000000000001
0000000000000000000000000000001
1000000000000000000000000000001
0000000000000000000000000000001
1111111111111111111111111111111

If you look at the pattern, you can convince yourself that the number of losses is equal to

    [ (n+1)//2 + 2 * ((n+1)//4) + 4 * ((n+1)//8) + 8 * ((n+1)//16) + ... ] * 2 - log2(n)

The `* 2` factor around the square brackets is because the pattern is symmetric about the diagonal of the grid, i.e.
interchanging a and b. The `- log2(n)` is to account for overcounting along the diagonal of the grid.

ANSWER 10784223938983273

*/


void draw_grid(int size)
{
    // tracks loss (1) and win (0)
    Eigen::ArrayXXi grid(size, size);

    // populate for a=1 and b=1
    for (int i = 1; i < size; ++i) {
        grid(1, i) = i % 2;
        grid(i, 1) = i % 2;
    }

    for (int a = 2; a < size; ++a) {
        for (int b = a; b < size; ++b) {
            // with optimal strategy, we win if we can move to a losing state
            bool found_loss = false;
            for (int sub_from_a = 0; sub_from_a < a; ++sub_from_a) {
                const int sub_from_b = a - sub_from_a;
                if (sub_from_b >= b) {
                    continue;
                }
                if (grid(a - sub_from_a, b - sub_from_b) == 1) {
                    found_loss = true;
                    break;
                }
            }

            // update (a, b) and (b, a)
            if (found_loss) {
                grid(a, b) = 0;
                grid(b, a) = 0;
            } else {
                grid(a, b) = 1;
                grid(b, a) = 1;
            }
        }
    }

    // print grid
    int count_losses = 0;
    for (int row = 1; row < size; ++row) {
        for (int col = 1; col < size; ++col) {
            printf("%d", grid(row, col));
            count_losses += grid(row, col);
        }
        printf("\n");
    }
    printf("num losses = %d\n", count_losses);
}


/**
 * Compute log2(n), truncating down to the nearest integer.
 */
int compute_log2(long n)
{
    assert(n > 0);
    int count = 0;
    while (n > 1) {
        n >>= 1;
        ++count;
    }
    return count;
}

long p0()
{
    // draw_grid(50);

    const long N = std::pow(7, 17);
    const long Np1 = N + 1;

    const int log2 = compute_log2(Np1);

    long sum = 0;

    long power_of_two = 2;
    for (int k = 1; k <= log2; ++k) {
        sum += (power_of_two / 2) * (Np1 / power_of_two);
        power_of_two *= 2;
    }

    return 2 * sum - log2;
}

int main()
{
    printf("%ld\n", p0());
}
