#include "../include/string.h"

char* strncat(char* restrict dest, const char* restrict src, size_t n)
{
	char* restrict d = dest;
    const char* restrict s = src;
    d += strlen(dest);
    for (; n && (*d = *s); n--, d++, s++) 
        ;
    *d = '\0';
    return dest;
}