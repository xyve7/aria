#include "../include/string.h"

char* strncpy(char* restrict dest, const char* restrict src, size_t n)
{
    char * d = dest;
    const char * s = src;
    for(; n && *s; n--)
    {
		*d++ = *s++;
	}
	for(;n != 0; n--)
	{
		*d++ = '\0';
	}
    return dest;
}