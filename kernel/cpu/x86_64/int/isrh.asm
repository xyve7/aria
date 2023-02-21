%include "cpu/x86_64/cpuh.asm"
; Defines all of the isr stubs
%macro isr_err_stub 1
isr_stub_%+%1:
	push %1
    jmp isr_trampoline 
%endmacro
%macro isr_no_err_stub 1
isr_stub_%+%1:
	push 0
	push %1
    jmp isr_trampoline
%endmacro

; All of the errors, with and without an error
extern isr_handler
isr_no_err_stub 0
isr_no_err_stub 1
isr_no_err_stub 2
isr_no_err_stub 3
isr_no_err_stub 4
isr_no_err_stub 5
isr_no_err_stub 6
isr_no_err_stub 7
isr_err_stub    8
isr_no_err_stub 9
isr_err_stub    10
isr_err_stub    11
isr_err_stub    12
isr_err_stub    13
isr_err_stub    14
isr_no_err_stub 15
isr_no_err_stub 16
isr_err_stub    17
isr_no_err_stub 18
isr_no_err_stub 19
isr_no_err_stub 20
isr_no_err_stub 21
isr_no_err_stub 22
isr_no_err_stub 23
isr_no_err_stub 24
isr_no_err_stub 25
isr_no_err_stub 26
isr_no_err_stub 27
isr_no_err_stub 28
isr_no_err_stub 29
isr_err_stub    30
isr_no_err_stub 31

; Pushes all the general purpose registers and calls the isr_handler
isr_trampoline:
	pushaq
	mov rdi, rsp
	call isr_handler
	popaq
	add rsp, 16
	iretq