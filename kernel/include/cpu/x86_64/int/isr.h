#ifndef ISR_H
#define ISR_H

#include <cpu/x86_64/cpu.h>
#include <libc/stdio.h>
#include <utils/log.h>

/**
 * @brief Interrupt Service Routine (ISR) handler.
 *
 * This function is invoked by the CPU when an interrupt occurs.
 * It takes an interrupt frame as its parameter, which contains information about the state of the CPU at the time of the interrupt.
 * This information can be used to determine the cause of the interrupt and take appropriate actions.
 *
 * @param sf Pointer to the interrupt frame.
 * @return This function does not return.
 * @note This function should not be called by the user manually
 */
noreturn void isr_handler(interrupt_frame* sf);

#endif /* ISR_H */
