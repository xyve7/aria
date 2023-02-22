#include <cpu/x86_64/dev/ps2/ps2.h>

void ps2_write(u16 port, u8 value) 
{
	/**
	 * Checks the second bit of the status register to see if the input buffer bit is clear.
	 * Hangs until it's set. 
	 */
	while((inb(ps2_status) & 2))
		;
	outb(port, value);
}
u8 ps2_read() 
{
	/**
	 * Checks the first bit of the status register to see if the output buffer bit is set.
	 * Hangs until it's set. 
	 */
	while(!(inb(ps2_status) & 1))
		;
	return inb(ps2_data);
}