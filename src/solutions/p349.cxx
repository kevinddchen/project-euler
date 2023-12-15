#include "common.h"

#include <array>
#include <vector>

/*

According to Wikipedia, the ant's behavior becomes predictable after 10,000
iterations. So we just need to simulate the first chaotic iterations, and then
once we know the predictable behavior we can extrapolate to the desired number
of iterations.

ANSWER 115384615384614952

*/

constexpr bool WHITE = false;
// constexpr bool BLACK = true;

constexpr int UP = 0;
constexpr int RIGHT = 1;
constexpr int DOWN = 2;
constexpr int LEFT = 3;

// when looking for a pattern in history of square colors, the pattern must be
// at least this length. set higher to reduce change of false positive
constexpr int PATTERN_THRESHOLD = 16;

template <size_t width>
struct Grid {
    std::array<std::array<bool, width>, width> squares;

    Grid()
    {
        // width must be even
        assert(width % 2 == 0);
        // initialize grid with white
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < width; y++) {
                squares[x][y] = WHITE;
            }
        }
    };

    bool& at(int x, int y)
    {
        const int half_width = width / 2;
        return squares.at(x + half_width).at(y + half_width);
    }

    void print() const
    {
        for (int y = 0; y < width; y++) {
            for (int x = 0; x < width; x++) {
                printf("%d", squares[x][y]);
            }
            printf("\n");
        }
        printf("\n");
    }
};

struct Ant {
    int x;
    int y;
    int direction;

    Ant() : x(0), y(0), direction(0) {}

    void move()
    {
        switch (direction) {
            case UP:
                y++;
                break;
            case RIGHT:
                x++;
                break;
            case DOWN:
                y--;
                break;
            case LEFT:
                x--;
                break;
        }
    }

    inline void cw() { direction = (direction + 1) % 4; }

    inline void ccw() { direction = (direction + 3) % 4; }
};

/*
 * Find a repeating pattern in the history of square colors.
 */
bool find_pattern(const std::vector<char>& history)
{
    assert(history.size() % 2 == 0);  // length must be even
    int half_length = history.size() / 2;

    for (int i = 0; i < half_length; i++) {
        if (history.at(i) != history.at(i + half_length)) {
            return false;
        }
    }
    return true;
}

long p349()
{
    constexpr long limit = 1'000'000'000'000'000'000;
    constexpr long warmup = 10'000;  // number of iters to exit chaotic regime

    Grid<100> grid;
    Ant ant;

    /*
     * Make a step with the ant. Returns original color of the square.
     */
    auto step = [&]() -> bool {
        bool& square = grid.at(ant.x, ant.y);
        if (square == WHITE) {
            ant.cw();
        } else {
            ant.ccw();
        }

        ant.move();
        square = !square;

        return !square;
    };

    // chaotic behavior
    long n_black_squares_chaos = 0;
    for (int i = 0; i < warmup; i++) {
        if (step() == WHITE) {
            n_black_squares_chaos++;
        } else {
            n_black_squares_chaos--;
        }
    }

    // emergent order
    // find the pattern in black squares
    std::vector<char> history = {};

    while (true) {
        const bool square = step();
        history.push_back(square);

        if (history.size() % 2 == 0 && history.size() >= PATTERN_THRESHOLD * 2) {
            if (find_pattern(history)) {
                break;
            }
        }
    }

    const long pattern_length = history.size() / 2;

    // now that we know the pattern, we just need to count the black squares

    long n_black_squares_pattern = 0;
    for (int i = 0; i < pattern_length; i++) {
        if (history.at(i) == WHITE) {
            n_black_squares_pattern++;
        } else {
            n_black_squares_pattern--;
        }
    }

    long n_black_squares = n_black_squares_chaos + n_black_squares_pattern * ((limit - warmup) / pattern_length);
    for (int i = 0; i < (limit - warmup) % pattern_length; i++) {
        if (history.at(i) == WHITE) {
            n_black_squares++;
        } else {
            n_black_squares--;
        }
    }

    return n_black_squares;
}

int main()
{
    printf("%ld\n", p349());
}
