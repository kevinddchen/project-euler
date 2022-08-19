#pragma once

#include <cstdio>
#include <ctime>

#define TIMED(expr)                                          \
    {                                                        \
        clock_t t = clock();                                 \
        expr;                                                \
        t = clock() - t;                                     \
        printf("Time: %.3f\n", ((float)t) / CLOCKS_PER_SEC); \
    }

#ifdef NDEBUG
#define LOG(...) ((void)0)
#else
#define LOG(...) printf(__VA_ARGS__)
#endif
