#ifndef IRQ_H
#define IRQ_H

#include <cpu/x86_64/int/pic.h>

/**
 * @brief Interrupt Request (IRQ) handler.
 *
 * This function is invoked by the CPU when an interrupt occurs.
 * It takes an interrupt frame as its parameter, which contains information about the state of the CPU at the time of the interrupt.
 * This function is used to appropriately route to the correct handler for the IRQ device.
 *
 * @param sf Pointer to the interrupt frame.
 * @note This function should not be called by the user manually
 */
void irq_handler(interrupt_frame* sf);
void irq_install_handler(u8 index, void* handler);
void irq_uninstall_handler(u8 index);

#endif /* IRQ_H */
