#include "common.h"

#include <algorithm>

/*

Given an area of WxH, if we consider rectangles with width w and height h, then
the top-left corner must have a x value in [0, W-w] and a y value in [0, H-h].
So there are (1+W-w)*(1+H-h) rectangles in this area. But if we consider all
smaller areas as well, then there are T(1+W-w)*T(1+H-h) rectangles, where T(n)
is the nth triangle number.

The same logic applies for the rectangles along diagonals, but there are two
types: those whose left-most corner lies on the integer lattice, i.e. (n, m),
and those whose left-most corner lies on the half-integer lattice, i.e. (n+1/2,
m+1/2).

ANSWER 846910284

*/

inline int triangle(int n)
{
    return n * (n + 1) / 2;
}

inline int half_round_up(int n)
{
    return (n + 1) / 2;
}

long p147()
{
    const int W = 47;
    const int H = 43;

    long total_count = 0;

    // rectangles of width w and height h
    // coordinate of top-right corner:
    // x in [0, W-w]
    // y in [0, H-w]
    for (int w = 1; w <= W; w++) {
        for (int h = 1; h <= H; h++) {
            const int x_count = 1 + W - w;
            const int y_count = 1 + H - h;
            total_count += triangle(x_count) * triangle(y_count);
        }
    }

    // rectangles with u units of (1/2, 1/2) and d units of (1/2, -1/2)
    // coordiante of left-most corner:
    // x in [0, W-(u+d)/2]
    // y in [u/d, H-d/2]
    for (int u = 1; u <= 2 * std::min(W, H); u++) {  // TODO: better bound?
        for (int d = 1; u + d <= 2 * std::min(W, H); d++) {
            // integer lattice
            {
                const int x_count = 1 + W - half_round_up(u + d);
                const int y_count = 1 + H - half_round_up(u) - half_round_up(d);
                total_count += triangle(x_count) * triangle(y_count);
            }
            // half-integer lattice
            {
                const int x_count = 1 + W - half_round_up(u + d + 1);
                const int y_count = 1 + H - half_round_up(u - 1) - half_round_up(d + 1);
                total_count += triangle(x_count) * triangle(y_count);
            }
        }
    }
    return total_count;
}

int main()
{
    printf("%ld\n", p147());
}
