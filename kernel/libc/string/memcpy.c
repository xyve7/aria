#include "../include/string.h"

void* memcpy(void * restrict dest, const void * restrict src, size_t n)
{
    unsigned char * d = dest;
    const unsigned char * s = src;
    for (; n && (*d = *s); n--, s++, d++)
        ;
    return dest;
}