#include <cpu/x86_64/int/idt.h>
#include <bitmanip.h>

/**
 * @brief Table that contains all of the handlers. Populated via assembly.
 * 
 * This contains all of the function pointers to the handler methods.
 * 
 * @note The first 32 are exceptions, the next 16 are hardware interrupts, the rest are software interrupts.
 */
extern void* int_handler_table[];

/**
 * @brief Interrupt Descriptor Table (IDT)
 * 
 * The IDT is a table that contains entries describing interrupt gates used for interrupt handling.
 * Each entry in the IDT contains a handler address and a set of flags.
 * When an interrupt occurs, the CPU uses the interrupt number to index the IDT and find the corresponding entry.
 * The handler address in the entry is then used to execute the corresponding interrupt handler.
 * 
 * @note This struct is aligned by 0x10 (16) to increase performance
 */
aligned(0x10) static idt_entry idt[256];
static idtr idtptr;

/**
 * @brief Sets the Interrupt Descriptor Table (IDT) Entry (or Gate).
 * 
 * @param index The index of which entry you want to set.
 * @param handler The address of the handler (cast is as a u64).
 * @param attr The attributes (of flags). This tells us if its an trap gate or interrupt gate.
 */
void idt_set_gate(u8 index, u64 handler, u8 attr) {
	idt[index].isr0 = (u16)word_0(handler);
	idt[index].kernel_cs = kernel_64_code_seg;
	idt[index].ist = 0;
	idt[index].attr = attr;
	idt[index].isr1 = (u16)word_1(handler);
	idt[index].isr2 = (u32)dword_1(handler);
	idt[index].reserved = 0;
}
/**
 * @brief Initializes the Interrupt Descriptor Table (IDT).
 * 
 * It defines the Interrupt Descriptor Table Register (IDTR) and loads it with the "lidt" instruction.
 * 
 * @return idt_response
 */
idt_response idt_init(void) {

	for (u64 i = 0; i < 32; i++) {
		idt_set_gate(i, int_handler_table[i], 0x8E);
	}

	idtptr.address = (u64)&idt[0];
	idtptr.size = (u16)(sizeof(idt_entry) * 256 - 1);

	__asm__ __volatile__("lidt %0" :: "m" (idtptr));

	return (idt_response){.idtr = idtptr, int_handler_table, 32};
}