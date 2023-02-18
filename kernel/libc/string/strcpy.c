#include "../include/string.h"

char* strcpy(char* restrict dest, const char* restrict src)
{
    char * d = dest;
    const char * s = src;
    for (;*s && (*d = *s); d++, s++) 
        ;
    *d = '\0';
    return dest;
}