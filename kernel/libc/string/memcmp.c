#include "../include/string.h"

int memcmp(const void* ptr1, const void* ptr2, size_t n)
{
    const unsigned char* p1 = ptr1;
    const unsigned char* p2 = ptr2;
    for (; n && (*p1 == *p2); n--, p1++, p2++)
        ;
    return (*p1 - *p2);
}