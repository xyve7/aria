#ifndef IDT_H
#define IDT_H

#include <kernel.h>
#include <utils/log.h>

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
 * @brief Sets the Interrupt Descriptor Table (IDT) Entry (or Gate).
 * 
 * @param index The index of which entry you want to set.
 * @param handler The address of the handler (cast is as a u64).
 * @param attr The attributes (of flags). This tells us if its an trap gate or interrupt gate.
 */
void idt_set_gate(u8 index, u64 handler, u8 attr);
/**
 * @brief Initializes the Interrupt Descriptor Table (IDT).
 * 
 * It defines the Interrupt Descriptor Table Register (IDTR) and loads it with the "lidt" instruction.
 * 
 * @return idt_response
 */
void idt_init(void);

#endif /* IDT_H */
