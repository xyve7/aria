#include <stdint.h>
#include <stddef.h>
#include <libc/stdio.h>
#include <cpu/x86_64/int/idt.h>

void _start(void) {
	idt_response ridt = idt_init();

	printf("interrupt descriptor table:\n");
	printf("\tsize: %lX (%lu)\n", ridt.idtr.size, ridt.idtr.size);
	printf("\taddress: %lX\n", ridt.idtr.address);
	for (u64 i = 0; i < ridt.size; i++) {
		printf("\t%lu: %p\n", i, ridt.int_handlers[i]);
	}
	
    printf("Hello World!\n");

	__asm__ __volatile__("int $0");
	hang();
}
