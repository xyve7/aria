#ifndef STDIO_H
#define STDIO_H

#include <libc/printf.h>
#include <term/term.h>

int puts(const char* str);
int putchar(int c);
void _putchar(char c);

#endif // STDIO_H