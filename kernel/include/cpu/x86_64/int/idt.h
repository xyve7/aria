#ifndef IDT_H
#define IDT_H

#include <kernel.h>

/**
 * @brief Interrupt Descriptor Table (IDT) Entry
 *
 * This structure is an entry for the Interrupt Descriptor Table (IDT), which is used by the CPU to manage interrupts.
 *
 * @note This struct is packed to ensure correct alignment and no padding bits.
 */
typedef struct packed {
    u16 isr0;      ///< Lower 16 bits of the interrupt handler (Bits 0-15).
    u16 kernel_cs; ///< Kernel code segment selector.
    u8 ist;        ///< Interrupt stack table. Set to 0 if unused.
    u8 attr;       ///< Attribute byte. Contains information about the type of the interrupt and the privilege.
    u16 isr1;      ///< Middle 16 bits of the interrupt handler (Bits 16-31).
    u32 isr2;      ///< Higher 32 bits of the interrupt handler (Bits 32-63).
    u32 reserved;  ///< Reserved. Must be zero.
} idt_entry;

/**
 * @brief Interrupt Descriptor Table Register (IDTR).
 *
 * This structure is used by the "lidt" command to load in the Interrupt Descriptor Table (IDT).
 */
typedef struct packed {
    u16 size;     ///< The size of each entry in the IDT.
    u64 address;   ///< The base address of the IDT.
} idtr;

/**
 * @brief Interrupt Descriptor Table (IDT) Response
 * 
 * This structure is just the response from the "idt_init(void)" function.
 * 
 */
typedef struct {
	idtr idtr;
	void** int_handlers;
	u64 size;
} idt_response;

void idt_set_gate(u8 index, u64 handler, u8 attr);
idt_response idt_init(void);

#endif // IDT_H