#include <cpu/x86_64/int/isr.h>
const char* exceptions[] = {
    "Divide Error",
    "Debug Exception",
    "NMI Interrupt",
    "Breakpoint",
    "Overflow",
    "BOUND Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "x87 FPU Floating-Point Error",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Security Exception",
    "Reserved"
};
noreturn void isr_handler(interrupt_frame* sf)
{
	vlog_error("%s exception has occurred.\n", exceptions[sf->int_no]);
	printf("\tDump:\n");
	printf("\trax=%016lX rbx=%016lX rcx=%016lX rdx=%016lX\n", sf->rax, sf->rbx, sf->rcx, sf->rdx);
	printf("\trdi=%016lX rsi=%016lX rbp=%016lX rsp=%016lX\n", sf->rdi, sf->rsi, sf->rbp, sf->rsp);
	printf("\tr8=%016lX r9=%016lX r10=%016lX r11=%016lX\n", 	sf->r8,  sf->r9,  sf->r10, sf->r11);
	printf("\tr12=%016lX r13=%016lX r14=%016lX r15=%016lX\n", sf->r12, sf->r13, sf->r14, sf->r15);

	printf("\trip=%016lX rflags=%016lX rsp=%016lX\n", sf->rip, sf->rflags, sf->rsp);
	printf("\tcs=%016lX ss=%016lX\n", sf->cs, sf->ss);
	printf("\tint_no=%016lX err_code=%016lX\n", sf->int_no, sf->err_code);

	hang();
}