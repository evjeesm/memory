#include "memswap.h"

void memswap(char *restrict a, char *restrict b, const size_t size)
{
    for (size_t i = 0; i < size / sizeof(size_t); ++i)
    {
        *(size_t*)a ^= *(size_t*)b;
        *(size_t*)b ^= *(size_t*)a;
        *(size_t*)a ^= *(size_t*)b;
        a += sizeof(size_t);
        b += sizeof(size_t);
    }
    for (size_t i = 0; i < size % sizeof(size_t); ++i, ++a, ++b)
    {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
}
