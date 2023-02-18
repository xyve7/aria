#include "../include/string.h"

char* strcat(char* restrict dest, const char* restrict src)
{
    char* restrict d = dest;
    const char* restrict s = src;
    d += strlen(dest);
    for (; *s && (*d = *s); d++, s++) 
        ;
    *d = '\0';
    return dest;
}