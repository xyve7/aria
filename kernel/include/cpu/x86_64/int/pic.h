#ifndef PIC_H
#define PIC_H

#include <cpu/x86_64/cpu.h>
#include <bitmanip.h>
#include <utils/log.h>

#define pic1_command 0x20
#define pic1_data 	 0x21
#define pic2_command 0xA0
#define pic2_data 	 0xA1

#define pic_init_cmd 0x11
#define pic_8086_cmd 0x01
#define pic_eoi_cmd  0x20

/**
 * Here is something that is slightly more complicated.
 * 
 * The PIC is responsible for handling hardware interrupts.
 * Let's use the keyboard as an example.
 * When a key is pressed, the keyboard tells the PIC to fire an interrupt.
 * The interrupt is then handled by the interrupt handler.
 * 
 * Generally, the PIC fires interrupt 0 - 7 for the first PIC, and 8 - 15 for the second PIC.
 * However, this conflicts with the first 32 interrupts, as they are exceptions.
 * 
 * This was a design mistake by IBM, so to fix this, we have to remap the PIC and change the offset.
 * We change the offset of the first PIC to start at 32 - 39, and the second one to 40 - 47.
 * This makes sure that the interrupts from the PIC don't interfere with the interrupts for the exceptions.
 * 
 * And that's why in the idt.c file, I specify that the first 32 are exceptions, the next 16 are hardware interrupts, and the rest are normal software interrupts.
 */

/**
 * @brief Sets the mask for the given IRQ number
 * @param irq The IRQ number to set the mask for
 * 
 * This function sets the mask for the given IRQ number.
 * If the IRQ number is greater than 7, the mask will be set on the slave PIC, otherwise it will be set on the master PIC.
 * To set the mask, the bit corresponding to the IRQ number in the PIC's mask register is set to 1.
 */
void pic_set_mask(u8 irq);
/**
 * @brief Clears the mask for the given IRQ number
 * @param irq The IRQ number to clear the mask for
 * 
 * This function clears the mask for the given IRQ number.
 * If the IRQ number is greater than 7, the mask will be cleared on the slave PIC, otherwise it will be cleared on the master PIC.
 * To clear the mask, the bit corresponding to the IRQ number in the PIC's mask register is set to 0.
 */
void pic_clear_mask(u8 irq);
/**
 * @brief Sends the End of Interrupt (EOI) signal to the PIC
 * @param irq The IRQ number that is being serviced
 * 
 * This function sends the End of Interrupt (EOI) signal to the PIC after an interrupt has been serviced.
 * If the IRQ number is greater than 7, the EOI signal will be sent to the slave PIC, otherwise it will be sent to the master PIC.
 * The EOI signal notifies the PIC that the interrupt has been serviced and that it can start processing the next interrupt.
 */
void pic_send_eoi(u8 irq);
/**
 * @brief Initializes the Programmable Interrupt Controller (PIC)
 * 
 * This function initializes the Programmable Interrupt Controller (PIC) and saves the current IRQ masks.
 */
void pic_init(void);

#endif/* PIC_H */
