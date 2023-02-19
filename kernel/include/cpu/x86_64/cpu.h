#ifndef CPU_H
#define CPU_H

#include <kernel.h>

typedef struct packed {
	u64 r15;
	u64 r14;
	u64 r13;
	u64 r12;
	u64 r11;
	u64 r10;
	u64 r9;
	u64 r8;
	u64 rdi;
	u64 rsi;
	u64 rbp;
	u64 rbx;
	u64 rdx;
	u64 rcx;
	u64 rax;
	u64 int_no;
	u64 err_code;
	u64 rip;
	u64 cs;
	u64 rflags;
	u64 rsp;
	u64 ss;
} interrupt_frame;

#endif // CPU_H