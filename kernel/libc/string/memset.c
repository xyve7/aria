#include "../include/string.h"

void* memset(void* dest, int c, size_t n)
{
    unsigned char * d = dest;
    for (; n && (*d = c); n--, d++)
        ;
    return (void*)dest;
}