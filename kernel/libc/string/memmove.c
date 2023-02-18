#include "../include/string.h"

void* memmove(void *dest, const void *src, size_t n)
{
    unsigned char * d = dest;
    const unsigned char * s = src;
    if (s < d)
	{
        s += --n;
        d += --n;
        for (; (*d = *s); n--, d--, s--)
			;
    }
	else
	{
        for (; (*d = *s); n--, d++, s++)
			;
    }
    return dest;
}