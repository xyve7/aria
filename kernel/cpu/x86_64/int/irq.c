#include <cpu/x86_64/int/irq.h>

void irq_handler(interrupt_frame* sf)
{
	vlog_info("Hardware interrupt has occurred! %u\n", sf->int_no);
	/**
	 * Subtracts the int_no by 32, as all of the values of int_no will be 32 or higher, and since this is an IRQ, the highest value can only be 15.
	 * Subtracting it by 32 will give the PIC the appropriate value.
	 */
	pic_send_eoi(sf->int_no - 32);
}