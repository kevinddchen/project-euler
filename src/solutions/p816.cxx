#include "common.h"
#include "generator.h"
#include "mathfuncs.h"

#include <Eigen/Core>

/*

Finding the nearest-neighbor for each point is significantly sped up by using a
grid to keep track of points in the same neighborhood. So we never have to
compare points that are too far away from each other.

ANSWER 20.880613018

*/

using Vec2l = Eigen::Matrix<long, 2, 1>;
using Vec2i = Eigen::Matrix<int, 2, 1>;

/*
 * Given a point on a square grid of size n_cells x n_cells, return the points
 * (in any order) of the square ring centered at this point with the given
 * radius.
 */
std::vector<Vec2i> get_indices_at_radius(const Vec2i& center, int n_cells, int radius)
{
    if (radius == 0) {
        return {center};
    }

    std::vector<Vec2i> indices;
    const int x = center.x();
    const int y = center.y();

    if (x - radius >= 0) {
        for (int i = std::max(0, y - radius); i <= std::min(n_cells - 1, y + radius); i++) {
            indices.push_back(Vec2i(x - radius, i));
        }
    }
    if (x + radius < n_cells) {
        for (int i = std::max(0, y - radius); i <= std::min(n_cells - 1, y + radius); i++) {
            indices.push_back(Vec2i(x + radius, i));
        }
    }
    if (y - radius >= 0) {
        for (int i = std::max(0, x - radius + 1); i <= std::min(n_cells - 1, x + radius - 1); i++) {
            indices.push_back(Vec2i(i, y - radius));
        }
    }
    if (y + radius < n_cells) {
        for (int i = std::max(0, x - radius + 1); i <= std::min(n_cells - 1, x + radius - 1); i++) {
            indices.push_back(Vec2i(i, y + radius));
        }
    }

    return indices;
}

/*
 * Data structure to compute nearest-neighbors efficiently by organizing points
 * into a grid.
 */
struct PointGrid {
    std::vector<Vec2l>** grid;
    const int n_cells;
    const int cell_size;

    PointGrid(int n_cells, int cell_size) : n_cells(n_cells), cell_size(cell_size)
    {
        // allocate heap memory because stack is too small
        grid = new std::vector<Vec2l>*[n_cells];
        for (int i = 0; i < n_cells; i++) {
            grid[i] = new std::vector<Vec2l>[n_cells];
        }
    }

    ~PointGrid()
    {
        for (int i = 0; i < n_cells; i++) {
            delete[] grid[i];
        }
        delete[] grid;
    }

    /*
     * Given a point, return the grid index.
     */
    inline Vec2i get_index(const Vec2l& p) const
    {
        const int x = p.x() / cell_size;
        const int y = p.y() / cell_size;
        return Vec2i(x, y);
    }

    /*
     * Add a point to the grid.
     */
    void add_point(Vec2l p)
    {
        const Vec2i p_idx = get_index(p);
        grid[p_idx.x()][p_idx.y()].push_back(std::move(p));
    }

    /*
     * Given a point in the grid, compute the distance to its nearest neighbor.
     * :param p: the point to compute the distance for
     * :param radius: the radius of the square ring to search for neighbors
     * :return: the best distance found
     */
    double nearest_neighbor_distance(
        const Vec2l& p, int radius = 0, double best = std::numeric_limits<double>::max()) const
    {
        // we exit if we cannot find a better distance
        // radius is increasing and best is decreasing, so we will terminate eventually
        if (best < (radius - 1) * cell_size) {
            return best;
        }

        const Vec2i p_idx = get_index(p);

        // get all points in cells `radius` away
        std::vector<Vec2l> points;
        if (radius == 0) {
            for (const Vec2l& q : grid[p_idx.x()][p_idx.y()]) {
                if (q != p) {
                    points.push_back(q);
                }
            }
        } else {
            for (const Vec2i& q_idx : get_indices_at_radius(p_idx, n_cells, radius)) {
                for (const auto& q : grid[q_idx.x()][q_idx.y()]) {
                    points.push_back(q);
                }
            }
        }

        // compute distance to all points in the square ring
        for (const Vec2l& q : points) {
            const Vec2l disp = p - q;
            const double dist = sqrt(disp.dot(disp));
            if (dist < best) {
                best = dist;
            }
        }

        // recurse to next square ring
        return nearest_neighbor_distance(p, radius + 1, best);
    }
};

double p816()
{
    constexpr int limit = 2'000'000;

    mf::BlumBlumShub bbs;
    const int n_cells = 1000;
    const int cell_size = (bbs.mod / n_cells) + 1;

    // create a grid to help nearest-neighbor search
    PointGrid pg(n_cells, cell_size);

    // generate points and populate grid
    for (int i = 0; i < limit; i++) {
        const int x = *bbs++;
        const int y = *bbs++;
        pg.add_point({x, y});
    }

    // for each point, find the nearest neighbor
    bbs = mf::BlumBlumShub();
    double min_dist = std::numeric_limits<double>::max();
    for (int i = 0; i < limit; i++) {
        const int x = *bbs++;
        const int y = *bbs++;

        const double dist = pg.nearest_neighbor_distance({x, y});

        if (dist < min_dist) {
            min_dist = dist;
        }
    }

    return min_dist;
}

int main()
{
    TIMED(printf("%.9f\n", mf::round(p816(), 9)));
}
