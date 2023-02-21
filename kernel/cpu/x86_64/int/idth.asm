%include "cpu/x86_64/int/irqh.asm"
%include "cpu/x86_64/int/isrh.asm"
; Populates the int_header_table in the idt.c file with the first 32 isrs and the rest of the 16 irqs.
global int_handler_table
int_handler_table:
%assign i 0 
%rep    32 
    dq isr_stub_%+i 
%assign i i+1 
%endrep
%assign i 32 
%rep    16 
    dq irq_stub_%+i 
%assign i i+1 
%endrep