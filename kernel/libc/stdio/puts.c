#include <libc/stdio.h>

int puts(const char* str)
{
	term_print(str);
	return 0;
}