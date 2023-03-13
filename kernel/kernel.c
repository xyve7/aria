#include <stdint.h>
#include <stddef.h>
#include <libc/stdio.h>
#include <cpu/x86_64/int/idt.h>
#include <cpu/x86_64/rtc/rtc.h>
#include <cpu/x86_64/int/irq.h>
#include <cpu/x86_64/dev/ps2/keyboard.h>
#include <utils/log.h>
#include <sys/mm/pmm.h>

void _start(void) {
	rtc_init();
	cli();
	pic_init();
	sti();
	idt_init();
	keyboard_init();
	pmm_init();
	
	char* page = pmm_alloc(2) + 0xffff800000000000;
	memset(page, 'A', 8191);
	page[8191] = '\0';
	printf("%s %lu\n", page, strlen(page));

	pmm_free(page - 0xffff800000000000, 2);
	hang();
}
