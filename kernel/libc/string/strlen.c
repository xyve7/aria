#include "../include/string.h"

size_t strlen (const char* str)
{
    size_t len = 0;
    for(; *str; str++, len++)
        ;
    return len;
}