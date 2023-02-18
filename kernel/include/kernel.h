#ifndef KERNEL_H
#define KERNEL_H

#include <limine.h>

#define cli() __asm__ __volatile__("cli");
#define sti() __asm__ __volatile__("sti");
#define hlt() __asm__ __volatile__("hlt");
#define hang() for(;;) { __asm__ __volatile__("hlt"); }

#define packed __attribute__((packed))
#define aligned(alignment) __attribute__((aligned(alignment)))

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