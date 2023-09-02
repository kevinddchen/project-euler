#include "common.h"

#include <vector>

/*

We use a depth-first search through the quadtree, skipping regions whose pixels
are all of the same color. Since the curve of the circle is monotonic in a
region, we can check if it intersects the region by checking the colors of the
four corners.

ANSWER 313135496

*/

/**
 * Subdivision choices, in the order given by the problem. A "region"
 * corresponds to a sequence of these choices.
 */
enum Subdivision { TOP_LEFT = 0, TOP_RIGHT = 1, BOTTOM_LEFT = 2, BOTTOM_RIGHT = 3 };

/**
 * Pixel colors.
 */
enum Color { BLACK, WHITE };

/**
 * Get color of the pixel at coordinates (x, y).
 * @param x
 * @param y
 * @param radius Radius of the circle, i.e. 2^(N-1)
 */
Color query_color(long x, long y, long radius)
{
    const long dx = x - radius;
    const long dy = y - radius;

    if (dx * dx + dy * dy <= radius * radius) {
        return Color::BLACK;
    } else {
        return Color::WHITE;
    }
}

/**
 * Get the bottom-left-most pixel coordinates for the region corresponding to
 * the given sequence of subdivision choices.
 * @param region
 * @param N
 * @return Coordinates (x, y)
 */
std::pair<int, int> get_bottom_left_coordinate(const std::vector<Subdivision>& region, int N)
{
    int x = 0;
    int y = 0;
    for (int i = 0; i < region.size(); i++) {
        const Subdivision subdivision = region[i];
        const int size = 1 << (N - i - 1);
        switch (subdivision) {
            case Subdivision::TOP_LEFT:
                y += size;
                break;
            case Subdivision::TOP_RIGHT:
                x += size;
                y += size;
                break;
            case Subdivision::BOTTOM_LEFT:
                break;
            case Subdivision::BOTTOM_RIGHT:
                x += size;
                break;
        }
    }
    return {x, y};
}

/**
 * Given a region, check if all pixels are the same color.
 * @param region
 * @param N
 * @return `true` if all pixels are the same color
 */
bool check_same_color(const std::vector<Subdivision>& region, int N)
{
    assert(region.size() < N);

    // coordinates of the bottom left corner
    const auto [x, y] = get_bottom_left_coordinate(region, N);

    // coordinates of top right corner
    const int x_max = x + (1 << (N - region.size())) - 1;
    const int y_max = y + (1 << (N - region.size())) - 1;

    // get the color of the bottom left corner
    const int radius = 1 << (N - 1);
    const Color color = query_color(x, y, radius);

    // check color is same as other corners
    return color == query_color(x_max, y, radius) && color == query_color(x, y_max, radius) &&
           color == query_color(x_max, y_max, radius);
}

/**
 * Get the next region. This is donce by cycling through {TOP_LEFT, TOP_RIGHT,
 * BOTTOM_LEFT, BOTTOM_RIGHT} in order. If we are at the bottom right, then we
 * pop the stack and repeat.
 */
void next_region(std::vector<Subdivision>& region)
{
    while (true) {
        if (region.back() != Subdivision::BOTTOM_RIGHT) {
            region.back() = static_cast<Subdivision>(static_cast<int>(region.back()) + 1);
            break;
        } else {
            region.pop_back();
        }
    }
}

long p287()
{
    const int N = 24;

    int encoding_length = 1;  // start with "0"
    std::vector<Subdivision> stack = {Subdivision::TOP_LEFT};

    while (!stack.empty()) {
        if (stack.size() == N) {
            // at deepest level; forced to use "10" or "11" for this region
            encoding_length += 2;
            next_region(stack);
        } else {
            if (check_same_color(stack, N)) {
                // region can be represented with "10" or "11"
                encoding_length += 2;
                next_region(stack);
            } else {
                // add "0"; recurse deeper
                encoding_length += 1;
                stack.push_back(Subdivision::TOP_LEFT);
            }
        }
    }

    return encoding_length;
}

int main()
{
    TIMED(printf("%ld\n", p287()));
}
