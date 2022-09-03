#pragma once

#include <cstdio>
#include <ctime>

#define TIMED(expr)                                              \
    {                                                            \
        clock_t t = clock();                                     \
        expr;                                                    \
        t = clock() - t;                                         \
        printf("Time: %.3f sec\n", ((float)t) / CLOCKS_PER_SEC); \
    }
