#include <cstdio>
#include <ctime>
#include "mathfuncs.h"

/*

We are just counting the points (x, y) where x^2 + xy + 41y^2 <= LIMIT.

There are two symmetries of this quadratic form:

    i)  (x, y) <--> (-x, -y)
    ii) (x, y) <--> (x+y, -y)

As a consequence of i), we only need to count the points for x >= 0. We also
note that the region {x>0; y>0}, which we call region A, is mapped into the
region {y<0; x+y>0} under the symmetries. Also, the region {x>0; 2x+y<0}, which
we call region B, is mapped into the region {2x+y>0; x+y<0} under the
symmetries. Thus the goal is to count the number of points within regions A and
B which satisfy the inequality x^2 + xy + 41y^2 <= LIMIT, and then multiply
their sum by 4 to account for the entire xy-plane. We will also have to
consider boundaries between regions, but this is the general logic.

Within region A, incrementing x by 1 or incrementing y by 1 will increase the
value of the quadratic form. Similarly, within region B, performing (x, y) ->
(x+1, y-2) or (x, y) -> (x, y+1) will increase the value of the quadratic form.
The derivation of this fact is not straightforward to describe, but a useful
resource is the first chapter of John Conway's book "The Senual (quadratic)
Form". With these observations, we count the number of points in regions A and
B by finding the boundary of points satisfying the inequality.

ANSWER 4921370551019052

*/

// const long LIMIT = 1'000;
// const long LIMIT = 1'000'000;
const long LIMIT = 10'000'000'000'000'000;


inline long quad_form(long x, long y)
{
    return x*x + x*y + 41*y*y;
}


long p804()
{

    // STEP 1: find boundaries of region A
    const long x_bound = floor(sqrt(LIMIT));  // at y=0
    const long y_bound = floor(sqrt(LIMIT / 41.0));  // at x=0

    // STEP 2: count points in region A
    long count_a = 0;
    {
        long x = x_bound;
        for (long y = 1; y <= y_bound; y++)
        {
            while (x > 0 && quad_form(x, y) > LIMIT)
            {
                x--;
            }
            // printf("x=%ld, y=%ld\n", x, y);
            count_a += x;
        }
    }
    // printf("count_a=%ld\n", count_a);

    // STEP 3: find boundaries of region B
    // y_bound is the same as in region A, but in the -y diretion
    const long n_bound = floor(sqrt(LIMIT / 163.0)); // at x=n, y=2n

    // STEP 4: count points in region B
    long count_b = 0;
    {
        long x = 0, y = -y_bound;
        for (long n = 1; n <= n_bound; n++)
        {
            x += 1;
            y -= 2;

            while (-y - 2 * n > 0 && quad_form(x, y) > LIMIT)
            {
                y++;
            }
            // printf("x=%ld, y=%ld\n", x, y);
            count_b += -y - 2 * n;
        }
    }
    // printf("count_b=%ld\n", count_b);

    // STEP 5: add up all points
    // *4 for each region, *2 for each boundary
    return 4 * (count_a + count_b) + 2 * (x_bound + 2 * y_bound + n_bound);

}


int main()
{
    clock_t t;
    t = clock();
    printf("%ld\n", p804());
    t = clock()-t;
    printf("Time: %.3f\n", ((float) t)/CLOCKS_PER_SEC);
}
