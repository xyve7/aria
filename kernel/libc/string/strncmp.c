#include "../include/string.h"

int strncmp(const char* str1, const char* str2, size_t n)
{    
    for (; n && (*str1 == *str2); n--, str1++, str2++)
        ;
    return (*str1 - *str2);
}