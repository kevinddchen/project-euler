#include "common.h"
#include "containers.h"
#include "hash.h"

#include <numeric>
#include <unordered_set>
#include <vector>

/*

Finding the intersection of two line segments is a bit of geometry.

The tricky part is keeping track of the unique true intersection points. This
is done with perfect precision by recording the {p1/q1, p2/q1} rational
coordinates in a hash table.

ANSWER 2868868

*/

struct LineSeg {
    mf::Vec2l start;
    mf::Vec2l end;

    LineSeg(mf::Vec2l start, mf::Vec2l end) : start(start), end(end) {}
};

struct Intersect {
    mf::Frac x;
    mf::Frac y;

    Intersect() : x(0, 1), y(0, 1) {}

    Intersect(mf::Frac x, mf::Frac y) : x(x), y(y) {}

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
    //      a (l1.end - l1.start) + b (l2.end - l2.start) = l2.end - l1.start
    const auto d1 = l1.end - l1.start, d2 = l2.end - l2.start;
    const mf::Mat2l D = {d1.x, d2.x, d1.y, d2.y};  // {{d1.x, d2.x}, {d1.y, d2.y}}
    const auto det = D.det();
    if (det == 0) {
        // lines are parallel
        return false;
    }
    const auto rhs = l2.end - l1.start;
    const auto a_b_det = D.inv_times_det() * rhs;  // this equals {a, b} * det(D)
    const double a = a_b_det.x / (double)det;
    const double b = a_b_det.y / (double)det;

    // there is a true intersection if 0 < a < 1 and 0 < b < 1
    const bool is_true_intersect = (a > 0) && (a < 1) && (b > 0) && (b < 1);

    if (is_true_intersect) {
        intersect = {
            mf::Frac(l1.start.x) + mf::Frac(a_b_det.x * d1.x, det),
            mf::Frac(l1.start.y) + mf::Frac(a_b_det.x * d1.y, det)};
    }
    return is_true_intersect;
}

/*
 * Generates Blum Blum Shub sequence.
 */
struct BBSGen {
    static const long mod = 50'515'093;
    long s = 290'797;

    BBSGen() {}

    int next()
    {
        s = (s * s) % mod;
        return s;
    }
};

/*
 * Generates line segments based on the Blum Blum Shub sequence.
 */
struct LineSegGen {
    static const long size = 500;
    BBSGen bbs;

    LineSegGen() {}

    LineSeg next()
    {
        const int x1 = bbs.next() % size;
        const int y1 = bbs.next() % size;
        const int x2 = bbs.next() % size;
        const int y2 = bbs.next() % size;
        return LineSeg({x1, y1}, {x2, y2});
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
        const auto new_line = line_seg_gen.next();
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
        lines.push_back(new_line);
    }

    return count;
}

int main()
{
    TIMED(printf("%ld\n", p165()));
}
