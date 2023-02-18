#include <stdint.h>
#include <stddef.h>
#include <libc/stdio.h>

void _start(void) {
    printf("Hello World!");
	hang();
}
