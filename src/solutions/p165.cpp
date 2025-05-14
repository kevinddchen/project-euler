#include <mf/containers.hpp>
#include <mf/generators.hpp>
#include <mf/hash.hpp>

#include <Eigen/Core>
#include <Eigen/LU>

#include <unordered_set>
#include <vector>

/*

Finding the intersection of two line segments is a bit of geometry.

The tricky part is keeping track of the unique true intersection points. This
is done with perfect precision by recording the {p1/q1, p2/q1} rational
coordinates in a hash table.

ANSWER 2868868

*/

using Vec2l = Eigen::Matrix<long, 2, 1>;

struct LineSeg {
    Vec2l start;
    Vec2l end;

    LineSeg(Vec2l start, Vec2l end) : start(std::move(start)), end(std::move(end)) {}
};

struct Intersect {
    mf::Frac x;
    mf::Frac y;

    Intersect() : x(0, 1), y(0, 1) {}

    Intersect(mf::Frac x, mf::Frac y) : x(std::move(x)), y(std::move(y)) {}

    inline bool operator==(const Intersect& other) const { return x == other.x && y == other.y; }
};

// Intersect hash
template <>
struct std::hash<Intersect> {
    inline std::size_t operator()(const Intersect& intersect) const
    {
        return mf::hash::hash_combine(std::hash<mf::Frac>{}(intersect.x), std::hash<mf::Frac>{}(intersect.y));
    }
};

/*
 * Given two line segments, find their true intersection point. If the true
 * intersection does not exist, returns false.
 */
bool true_intersection(const LineSeg& l1, const LineSeg& l2, Intersect& intersect)
{
    // suppose we have two line segments l1, l2
    // we are solving the equation:
    //      l1.start + a (l1.end - l1.start) = l2.end + b (l2.start - l2.end)
    // or
    //      a (l1.end - l1.start) + b (l2.end - l2.start) = l2.end - l1.start
    const Vec2l d1 = l1.end - l1.start;
    const Vec2l d2 = l2.end - l2.start;
    // the LHS is now D * {a, b} where D is the matrix with columns d1, d2
    // D = {{d1.x, d2.x}, {d1.y, d2.y}}
    // let D_prime be the inverse of D times the determinant of D
    const Eigen::Matrix<long, 2, 2> D_prime{{d2.y(), -d2.x()}, {-d1.y(), d1.x()}};
    const long det = D_prime.determinant();
    if (det == 0) {
        // lines are parallel
        return false;
    }
    const Vec2l rhs = l2.end - l1.start;
    const Vec2l a_b_det = D_prime * rhs;  // this equals {a, b} * det(D)
    const double a = a_b_det.x() / static_cast<double>(det);
    const double b = a_b_det.y() / static_cast<double>(det);

    const bool is_true_intersect = (a > 0) && (a < 1) && (b > 0) && (b < 1);

    if (is_true_intersect) {
        intersect = {
            mf::Frac(l1.start.x()) + mf::Frac(a_b_det.x() * d1.x(), det),
            mf::Frac(l1.start.y()) + mf::Frac(a_b_det.x() * d1.y(), det)};
    }
    return is_true_intersect;
}

/*
 * Generates line segments based on the Blum Blum Shub sequence.
 */
struct LineSegGen {
    static const long size = 500;
    mf::BlumBlumShub bbs;

    LineSegGen()
    {
        bbs = mf::BlumBlumShub();
        ++bbs;  // discard s0
    }

    LineSeg next()
    {
        const int x1 = *bbs++ % size;
        const int y1 = *bbs++ % size;
        const int x2 = *bbs++ % size;
        const int y2 = *bbs++ % size;
        return LineSeg(Vec2l(x1, y1), Vec2l(x2, y2));
    }
};

long p165()
{
    constexpr int limit = 5000;

    std::vector<LineSeg> lines;
    std::unordered_set<Intersect> intersects;

    LineSegGen line_seg_gen;
    long count = 0;
    while (lines.size() < limit) {
        auto new_line = line_seg_gen.next();
        for (const auto& line : lines) {
            Intersect intersect;
            if (true_intersection(line, new_line, intersect)) {
                // If intersection point has not been seen before
                if (intersects.find(intersect) == intersects.end()) {
                    intersects.insert(intersect);
                    count++;
                }
            }
        }
        lines.push_back(std::move(new_line));
    }

    return count;
}

int main()
{
    printf("%ld\n", p165());
}
