#include "../include/string.h"

char* strchr(const char* str, int c)
{
    const char * s = str;
    for (; *s; s++)
    {
		if(*s == (unsigned char)c)
        {
			return (char*)s;
		}
	}
    return NULL;
}