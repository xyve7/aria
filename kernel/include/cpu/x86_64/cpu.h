#ifndef CPU_H
#define CPU_H

#include <kernel.h>

/**
 * @brief A structure representing the interrupt frame pushed onto the stack by the processor when an interrupt occurs.
 * 
 * This structure contains the state of the CPU at the time the interrupt was triggered. The packed attribute is used
 * to ensure that the structure is without any padding between the members.
 */
typedef struct packed {
    u64 r15;        ///< Value of the r15 register.
    u64 r14;        ///< Value of the r14 register.
    u64 r13;        ///< Value of the r13 register.
    u64 r12;        ///< Value of the r12 register.
    u64 r11;        ///< Value of the r11 register.
    u64 r10;        ///< Value of the r10 register.
    u64 r9;         ///< Value of the r9 register.
    u64 r8;         ///< Value of the r8 register.
    u64 rdi;        ///< Value of the rdi register.
    u64 rsi;        ///< Value of the rsi register.
    u64 rbp;        ///< Value of the rbp register.
    u64 rbx;        ///< Value of the rbx register.
    u64 rdx;        ///< Value of the rdx register.
    u64 rcx;        ///< Value of the rcx register.
    u64 rax;        ///< Value of the rax register.
    u64 int_no;     ///< Interrupt number.
    u64 err_code;   ///< Error code (if applicable).
    u64 rip;        ///< Instruction pointer value.
    u64 cs;         ///< Code segment value.
    u64 rflags;     ///< Flags register value.
    u64 rsp;        ///< Stack pointer value.
    u64 ss;         ///< Stack segment value.
} interrupt_frame;

static inline void outb(u16 port, u8 val)
{
    __asm__ __volatile__ ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}
static inline void outw(u16 port, u16 val)
{
    __asm__ __volatile__ ( "outw %0, %1" : : "a"(val), "Nd"(port) );
}
static inline void outl(u16 port, u32 val)
{
    __asm__ __volatile__ ( "outl %0, %1" : : "a"(val), "Nd"(port) );
}
static inline u8 inb(u16 port)
{
    u8 ret;
    __asm__ __volatile__ ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}
static inline u16 inw(u16 port)
{
    u16 ret;
    __asm__ __volatile__ ( "inw %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}
static inline u32 inl(u16 port)
{
    u32 ret;
    __asm__ __volatile__ ( "inl %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}

#endif/* CPU_H */
