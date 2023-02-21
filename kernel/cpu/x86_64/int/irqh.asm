%include "cpu/x86_64/cpuh.asm"

%macro irq_stub 1
irq_stub_%+%1:
	push 0
	push %1
    jmp irq_trampoline
%endmacro

; IRQ stubs, incremented by 32, as the hardware interrupts are after 32
extern irq_handler
irq_stub 32
irq_stub 33
irq_stub 34
irq_stub 35
irq_stub 36
irq_stub 37
irq_stub 38
irq_stub 39
irq_stub 40
irq_stub 41
irq_stub 42
irq_stub 43
irq_stub 44
irq_stub 45
irq_stub 46
irq_stub 47

; Pushes all the general purpose registers and calls the irq_handler
irq_trampoline:
	pushaq
	mov rdi, rsp
	call irq_handler
	popaq
	add rsp, 16
	iretq