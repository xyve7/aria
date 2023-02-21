#include <stdint.h>
#include <stddef.h>
#include <libc/stdio.h>
#include <cpu/x86_64/int/idt.h>
#include <cpu/x86_64/rtc/rtc.h>
#include <cpu/x86_64/int/irq.h>
#include <utils/log.h>

void _start(void) {
	rtc_init(true);
	cli();
	pic_init();
	sti();
	idt_init();
	pic_clear_mask(1);
	
	hang();
}
