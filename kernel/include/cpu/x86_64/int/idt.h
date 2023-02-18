#ifndef IDT_H
#define IDT_H

#include <kernel.h>
/**
 * @brief Interrupt Descriptor Table (IDT) Entry
 *
 * This packed struct represents an entry in the Interrupt Descriptor Table (IDT), which is used by the x86 architecture to manage interrupts.
 *
 * @note The members of this struct are packed to ensure correct alignment.
 */
typedef struct packed {
    u16 isr0;      ///< Offset bits 0-15 of the interrupt handler function.
    u16 kernel_cs; ///< Code segment selector in the GDT for the kernel code segment.
    u8 ist;        ///< Interrupt stack table index.
    u8 attr;       ///< Attribute byte. Contains information about the type and privilege level of the interrupt handler.
    u16 isr1;      ///< Offset bits 16-31 of the interrupt handler function.
    u32 isr2;      ///< Offset bits 32-63 of the interrupt handler function.
    u32 reserved;  ///< Reserved. Must be zero.
} idt_entry;





#endif // IDT_H