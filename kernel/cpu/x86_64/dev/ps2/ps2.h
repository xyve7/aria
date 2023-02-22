#ifndef PS2_H
#define PS2_H

#include <cpu/x86_64/cpu.h>

#define ps2_data    0x60 /* For both reading and writing */
#define ps2_status  0x64 /* For reading only */
#define ps2_command 0x64 /* For writing only */

/* I'm well aware that the ps2_status and ps2_command are the same, it's only there because I like it */

/**
 * You may be now wondering why the ps2_read function doesn't have a parameter for the port, here is the reason why.
 * 
 * There are 2 ports you can read from, 0x60 and 0x64.
 * The purpose of these functions is to make sure the buffer bit is set or cleared and hang until it is set or is clear before it can read or write.
 * This is due to the PS/2 controller requiring this.
 * 
 * But, the status register has no requirement like this, as the status register holds the buffer bit itself.
 * So that leaves only one left, 0x60, that has to be read from.
 * 0x60 is has to be read from in this manner, meaning the status register buffer bit has to be checked.
 * 
 * So, there is no point in having a port parameter, as the only port being read from is 0x60
 */
void ps2_write(u16 port, u8 value);
u8 ps2_read();

#endif /* PS2_H */
