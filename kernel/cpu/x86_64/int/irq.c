#include <cpu/x86_64/int/irq.h>

void* irq_handler_table[16] = {NULL};

void irq_install_handler(u8 index, void* handler)
{
	irq_handler_table[index] = handler;
}
void irq_uninstall_handler(u8 index)
{
	irq_handler_table[index] = 0;
}
void irq_handler(interrupt_frame* sf)
{
	u8 irq_no = sf->int_no - 32;
	void(*handler)(interrupt_frame*) = irq_handler_table[irq_no];
	
	if(handler != NULL)
	{
		handler(sf);
	}
	/**
	 * Subtracts the int_no by 32, as all of the values of int_no will be 32 or higher, and since this is an IRQ, the highest value can only be 15.
	 * Subtracting it by 32 will give the PIC the appropriate value.
	 */
	pic_send_eoi(irq_no);
}