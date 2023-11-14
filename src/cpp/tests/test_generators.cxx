#include "generators.h"
#include "testing.h"

void test_laggedfibonacci()
{
    printf("Testing `LaggedFibonacci`... ");

    mf::LaggedFibonacci gen;
    assert(*gen++ == 200007);
    assert(*gen++ == 100053);
    assert(*gen++ == 600183);
    assert(*gen++ == 500439);
    assert(*gen++ == 600863);

    // skip to 100th number
    for (int i = 0; i < 94; ++i) {
        ++gen;
    }

    assert(*gen++ == 586613);

    printf("Done!\n");
}

void test_blumblumshub()
{
    printf("Testing `BlumBlumShub`... ");

    mf::BlumBlumShub gen;
    assert(*gen++ == 290797);
    assert(*gen++ == 629527);
    assert(*gen++ == 13339144);
    assert(*gen++ == 15552512);
    assert(*gen++ == 17939732);

    // skip to 100th number
    for (int i = 0; i < 94; ++i) {
        ++gen;
    }

    assert(*gen++ == 13024232);

    printf("Done!\n");
}

int main()
{
    test_laggedfibonacci();
    test_blumblumshub();

    return 0;
}
