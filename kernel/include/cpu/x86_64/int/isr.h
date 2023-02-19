#ifndef ISR_H
#define ISR_H

#include <cpu/x86_64/cpu.h>
#include <libc/stdio.h>

interrupt void isr_handler(interrupt_frame* sf);

#endif // ISR_H