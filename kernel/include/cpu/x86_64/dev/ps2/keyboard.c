#include <cpu/x86_64/dev/ps2/keyboard.h>

void keyboard_handler(interrupt_frame* sf)
{
	(void) sf;
	printf("key=%x\n", ps2_read());
}
void keyboard_init()
{
	pic_clear_mask(1);
	irq_install_handler(1, &keyboard_handler);
}