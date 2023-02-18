#ifndef TERM_H
#define TERM_H

#include <stddef.h>
#include <kernel.h>

void term_print(const char* str);
void term_print_char(const char ch);
void term_printn(const char* str, size_t len);

#endif // TERM_H