#include <libc/stdio.h>

int putchar(int c)
{
	term_print_char((char)c);
	return 0;
}
void _putchar(char c)
{
	term_print_char(c);
}