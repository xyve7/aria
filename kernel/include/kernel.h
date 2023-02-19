#ifndef KERNEL_H
#define KERNEL_H

#include <limine.h>
/**
 * @brief Disable interrupts.
 *
 * This macro is equivalent to the x86 assembly instruction "cli", which
 * disables interrupts by clearing the IF (Interrupt Flag) bit in the RFLAGS
 * register.
 */
#define cli() __asm__ __volatile__("cli");

/**
 * @brief Enable interrupts.
 *
 * This macro is equivalent to the x86 assembly instruction "sti", which
 * enables interrupts by setting the IF (Interrupt Flag) bit in the RFLAGS
 * register.
 */
#define sti() __asm__ __volatile__("sti");

/**
 * @brief Enter a low-power state until the next interrupt occurs.
 *
 * This macro is equivalent to the x86 assembly instruction "hlt", which puts
 * the CPU into a low-power state until the next interrupt occurs.
 */
#define hlt() __asm__ __volatile__("hlt");

/**
 * @brief Hang the system by entering an infinite loop and halting the CPU.
 *
 * This macro puts the system into an infinite loop that just waits for an
 * interrupt to occur by calling hlt() repeatedly, effectively hanging the
 * system.
 */
#define hang() for(;;) { __asm__ __volatile__("hlt"); }


#define packed __attribute__((packed))
#define noreturn __attribute__((noreturn))
#define interrupt __attribute__((interrupt))
#define aligned(alignment) __attribute__((aligned(alignment)))

#define kernel_null_seg 0x0
#define kernel_16_code_seg 0x8
#define kernel_16_data_seg 0x10
#define kernel_32_code_seg 0x18
#define kernel_32_data_seg 0x20
#define kernel_64_code_seg 0x28
#define kernel_64_data_seg 0x30

#ifdef __INT8_TYPE__
typedef __INT8_TYPE__ i8;
#endif
#ifdef __INT16_TYPE__
typedef __INT16_TYPE__ i16;
#endif
#ifdef __INT32_TYPE__
typedef __INT32_TYPE__ i32;
#endif
#ifdef __INT64_TYPE__
typedef __INT64_TYPE__ i64;
#endif
#ifdef __UINT8_TYPE__
typedef __UINT8_TYPE__ u8;
#endif
#ifdef __UINT16_TYPE__
typedef __UINT16_TYPE__ u16;
#endif
#ifdef __UINT32_TYPE__
typedef __UINT32_TYPE__ u32;
#endif
#ifdef __UINT64_TYPE__
typedef __UINT64_TYPE__ u64;
#endif

#ifdef __INTPTR_TYPE__
typedef __INTPTR_TYPE__ iptr;
#endif
#ifdef __UINTPTR_TYPE__
typedef __UINTPTR_TYPE__ uptr;
#endif

static volatile struct limine_terminal_request terminal_request;

#endif // KERNEL_H