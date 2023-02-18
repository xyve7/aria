#ifndef KERNEL_H
#define KERNEL_H

#include <limine.h>

#define cli() __asm__ __volatile__("cli");
#define sti() __asm__ __volatile__("sti");
#define hlt() __asm__ __volatile__("hlt");
#define hang() for(;;) { __asm__ __volatile__("hlt"); }

static volatile struct limine_terminal_request terminal_request;

#endif // KERNEL_H