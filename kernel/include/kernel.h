#ifndef KERNEL_H
#define KERNEL_H

#include <limine.h>

/**
 * @brief Defines integer types of specific widths.
 * 
 * This code block defines various integer types such as i8, i16, i32, i64,
 * u8, u16, u32, u64, iptr, and uptr using preprocessor directives. These 
 * types are used to specify the bit widths of integers.
 * 
 * If the macro for a specific width of integer type is defined, it is used 
 * to define the corresponding type. For example, if the __UINT16_TYPE__ macro
 * is defined, it is used to define the u16 type as __UINT16_TYPE__. If a macro 
 * for a specific width of integer type is not defined, the corresponding type
 * is not defined either.
 * 
 * @note The typedefs for these types are defined conditionally based on whether
 * the corresponding preprocessor macros are defined by the compiler. Therefore, 
 * the availability of these types may depend on the compiler and the target 
 * architecture.
 */
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
#ifdef __UINT64_TYPE__
typedef __UINT64_TYPE__ size_t;
#endif
#ifdef __INTPTR_TYPE__
typedef __INTPTR_TYPE__ iptr;
#endif
#ifdef __UINTPTR_TYPE__
typedef __UINTPTR_TYPE__ uptr;
#endif

#define NULL ((void*)0)
#define bool u8
#define true 1
#define false 0

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

noreturn void kernel_panic(const char * msg, const char * file, const char * func, u32 line, ...);
#define panic(msg, ...) kernel_panic(msg, __FILE__, __func__, __LINE__, ##__VA_ARGS__)

#define kernel_null_seg 0x0
#define kernel_16_code_seg 0x8
#define kernel_16_data_seg 0x10
#define kernel_32_code_seg 0x18
#define kernel_32_data_seg 0x20
#define kernel_64_code_seg 0x28
#define kernel_64_data_seg 0x30

#define page_size 4096

/* Gotten from Limine: https://github.com/limine-bootloader/limine/blob/d1e4b9946cf61f3c91ca0ffabd4a5336100ba453/common/lib/misc.h */
#define DIV_ROUNDUP(a, b) ({ \
    __auto_type DIV_ROUNDUP_a = (a); \
    __auto_type DIV_ROUNDUP_b = (b); \
    (DIV_ROUNDUP_a + (DIV_ROUNDUP_b - 1)) / DIV_ROUNDUP_b; \
})

#define ALIGN_UP(x, a) ({ \
    __auto_type ALIGN_UP_value = (x); \
    __auto_type ALIGN_UP_align = (a); \
    ALIGN_UP_value = DIV_ROUNDUP(ALIGN_UP_value, ALIGN_UP_align) * ALIGN_UP_align; \
    ALIGN_UP_value; \
})

#define ALIGN_DOWN(x, a) ({ \
    __auto_type ALIGN_DOWN_value = (x); \
    __auto_type ALIGN_DOWN_align = (a); \
    ALIGN_DOWN_value = (ALIGN_DOWN_value / ALIGN_DOWN_align) * ALIGN_DOWN_align; \
    ALIGN_DOWN_value; \
})


static volatile struct limine_terminal_request terminal_request;
static volatile struct limine_hhdm_request hhdm_request;
static volatile struct limine_memmap_request memmap_request;

#endif/* KERNEL_H */
