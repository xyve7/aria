#include <cpu/x86_64/int/isr.h>

noreturn void isr_handler(interrupt_frame* sf)
{
	printf("exception has occurred!\n");
	printf("dump:\n");
	printf("rax=%016lX rbx=%016lX rcx=%016lX rdx=%016lX\n", sf->rax, sf->rbx, sf->rcx, sf->rdx);
	printf("rdi=%016lX rsi=%016lX rbp=%016lX rsp=%016lX\n", sf->rdi, sf->rsi, sf->rbp, sf->rsp);
	printf("r8=%016lX r9=%016lX r10=%016lX r11=%016lX\n", 	sf->r8,  sf->r9,  sf->r10, sf->r11);
	printf("r12=%016lX r13=%016lX r14=%016lX r15=%016lX\n", sf->r12, sf->r13, sf->r14, sf->r15);

	printf("rip=%016lX rflags=%016lX rsp=%016lX\n", sf->rip, sf->rflags, sf->rsp);
	printf("cs=%016lX ss=%016lX\n", sf->cs, sf->ss);
	printf("int_no=%016lX err_code=%016lX\n", sf->int_no, sf->err_code);

	hang();
}