#include <cpu/x86_64/int/pic.h>
void pic_set_mask(u8 irq)
{
	/* This means the IRQ mask should go to the slave PIC */
	if(irq > 7)
	{
		u8 mask = inb(pic2_data);
		bit_set(mask, (irq - 8)); /* Subtracts the value, since the, for example, the 8th value is the 0th value on the slave PIC */
		outb(pic2_data, mask);
	}
	/* This means the IRQ mask should go to the master PIC */
	else
	{
		u8 mask = inb(pic1_data);
		bit_set(mask, irq); /* Don't subtract, since it isn't going to the slave PIC, because the 1st IRQ is the 1st one on the master PIC */
		outb(pic1_data, mask);
	}
}
void pic_clear_mask(u8 irq)
{
	/* This means the IRQ mask should go to the slave PIC */
	if(irq > 7)
	{
		u8 mask = inb(pic2_data);
		bit_clear(mask, (irq - 8)); /* Subtracts the value, since the, for example, the 8th value is the 0th value on the slave PIC */
		outb(pic2_data, mask);
	}
	/* This means the IRQ mask should go to the master PIC */
	else
	{
		u8 mask = inb(pic1_data);
		bit_clear(mask, irq); /* Don't subtract, since it isn't going to the slave PIC, because the 1st IRQ is the 1st one on the master PIC */
		outb(pic1_data, mask);
	}
}
void pic_send_eoi(u8 irq)
{
	/**
	 * When an End of Interrupt (EOI) happens, the PIC has to be notified.
	 * 
	 * If the IRQ number was between 0-7, the EOI goes to the master ONLY.
	 * If the IRQ number was between 8-15, the EOI goes to the slave AND master.
	 */
	if(irq > 7)
		outb(pic2_command, pic_eoi_cmd);
	outb(pic1_command, pic_eoi_cmd);
}
void pic_init(void)
{
	/**
	 * The first goal of the PIC is to save the current IRQ masks.
	 * 
	 * What is the IRQ mask?
	 * The IRQ mask just tells the PIC which interrupts are enabled or disabled.
	 * When you mask an IRQ, you essentially tell it to NOT fire an interrupt when that interrupt happens.
	 * For example, if I hit the keyboard (which is IRQ 1), and IRQ 1 is masked, the interrupt won't be registered to the CPU.
	 * 
	 * This is helpful when you're doing performance critical tasks and don't want the CPU to be interrupted.
	 */

	/* To save the masks, you just have to call "inb" to the PIC data port */
	u8 pic1_mask = inb(pic1_data);
	u8 pic2_mask = inb(pic2_data);

	/**
	 * This send the initialization to both of the PIC controllers.
	 * 
	 * This is to initialize the PIC and do 3 things:
	 * 		1. Changes the interrupt offset so it will call the correct interrupts
	 * 		2. Tell the PIC how it's wired (i.e. setup cascade more so the slave PIC can also be used) 
	 * 		3. Set the mode to 8086 mode
	 * 
	 * If I don't send the initialization command to the PIC, it will assume any data coming to the PIC data port is a mask.
	 * If we do, it will assume that the next 3 values coming in are the values i described above, and when the values have been satisfied, the initialization will be complete.
	 * And after the initialization is complete, any data coming to the PIC data port will be assumed to be a mask.
	 */
	outb(pic1_command, pic_init_cmd);
	outb(pic2_command, pic_init_cmd);

	/**
	 * Here is where I set the correct offset I was talking about earlier.
	 * 
	 * And since I enabled the initialization mode, it assumes this data is the interrupt offset 
	 */
	outb(pic1_data, 32); /* The 32 value is the start of the hardware interrupts in the interrupt descriptor table, as 0 - 31 are exceptions */
	outb(pic2_data, 40); /* And since each PIC chip handles 8 interrupts, 40 is the offset needed for the rest of the 8 for the slave PIC */

	/**
	 * Here it tells the master PIC that it's 3rd IRQ line, IRQ 2, is connected to the slave pic.
	 * 
	 * Next, it tells the slave PIC it's cascade identity. 
	 */
	outb(pic1_data, 4); /* The values is 4, because it's the 3rd bit. 4 in binary is 00000100 */
	outb(pic2_data, 2); /* The values is 2, because it's the 2nd bit in the ICW3 flag. 2 in binary is 00000010 */

	/**
	 * Now, for the last step in the initialization process, we set the mode to 8086/88 mode.
	 * 
	 * This is so that the PIC works correctly with x86. 
	 */
	outb(pic1_data, pic_8086_cmd);
	outb(pic2_data, pic_8086_cmd);

	/* Restores the PIC masks */
	outb(pic1_data, pic1_mask);
	outb(pic2_data, pic2_mask);

	vlog_info("Programmable Interrupt Controller (PIC) has been initialized\n");
}