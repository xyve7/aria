#include "../include/string.h"

char* strrchr(const char* str, int c)
{
    const char * s = str;
	char * save = NULL;
    for (; *s; s++)
    {
		if(*s == (unsigned char)c)
        {
			save = (char*)s;
		}
	}
    return save;
}