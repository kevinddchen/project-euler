#include "containers.h"
#include "testing.h"

void test_frac()
{
    printf("Testing `Frac`... ");

    const mf::Frac f1 = {3, 4};
    const mf::Frac f2 = {5, 2};

    assert(f1 == f1);
    assert(f1 != f2);
    assert(!(f1 == f2));
    assert(((mf::Frac){2, 2}) == ((mf::Frac){1, 1}));
    assert(((mf::Frac){1, -1}) == ((mf::Frac){-1, 1}));
    assert(f1 + f2 == ((mf::Frac){13, 4}));
    assert(-f1 == ((mf::Frac){-3, 4}));
    assert(f1 - f2 == ((mf::Frac){-7, 4}));
    assert(f1 - f2 == f1 + -f2);
    assert(f1 * f2 == ((mf::Frac){15, 8}));
    assert(f1.reciprocal() == ((mf::Frac){4, 3}));
    assert(is_equal(f1.fp(), 0.75));
    assert(is_equal((f1 * f1.reciprocal()).fp(), 1.0));

    printf("Done!\n");
}

int main()
{
    test_frac();

    return 0;
}
