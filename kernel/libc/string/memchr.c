#include "../include/string.h"

void* memchr(const void* src, int c, size_t n)
{
    const unsigned char * s = src;
    for (; n; n--, s++)
	{
		if(*s == (unsigned char)c)
        {
			return (void*)s;
		}
	}
    return NULL;
}