#include <stdint.h>
#include <stddef.h>
#include <libc/stdio.h>
#include <cpu/x86_64/int/idt.h>
#include <cpu/x86_64/rtc/rtc.h>
#include <utils/log.h>

void _start(void) {
	cli();
	idt_response ridt = idt_init();

	printf("interrupt descriptor table:\n");
	printf("\tsize: %04lX (%lu)\n", ridt.idtr.size, ridt.idtr.size);
	printf("\taddress: %016lX\n", ridt.idtr.address);
	for (u64 i = 0; i < ridt.size; i++) {
		printf("\t%lu: %p\n", i, ridt.int_handlers[i]);
	}
	
    printf("Hello World!\n");
	sti();

	rtc_init(true);

	log_debug("This is a test log\n");
	log_warn("This is a test log\n");
	log_error("This is a test log\n");
	log_info("This is a test log\n");
	
	hang();
}
