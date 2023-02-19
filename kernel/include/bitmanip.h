#ifndef BITMANIP_H
#define BITMANIP_H

#include <kernel.h>
/**
 * @brief Macros for extracting parts of a bit
 * 
 * This is made for convenience, and mostly to hide away the ugly casting garbage
 * 
 * @note These work with all unsigned numbers, however, it assumes you know the size of the number and dont do byte_2 on a 16 bit number or anything
 * 
 */
#define byte_0(x) ((u8)((x) & 0xff))
#define byte_1(x) ((u8)(((x) >> 8) & 0xff))
#define byte_2(x) ((u8)(((x) >> 16) & 0xff))
#define byte_3(x) ((u8)(((x) >> 24) & 0xff))
#define byte_4(x) ((u8)(((x) >> 32) & 0xff))
#define byte_5(x) ((u8)(((x) >> 40) & 0xff))
#define byte_6(x) ((u8)(((x) >> 48) & 0xff))
#define byte_7(x) ((u8)(((x) >> 56) & 0xff))

#define word_0(x) ((u16)((x) & 0xFFFF))
#define word_1(x) ((u16)(((x) >> 16) & 0xFFFF))
#define word_2(x) ((u16)(((x) >> 32) & 0xFFFF))
#define word_3(x) ((u16)(((x) >> 48) & 0xFFFF))

#define dword_0(x) ((u32)((x) & 0xFFFFFFFF))
#define dword_1(x) ((u32)(((x) >> 32) & 0xFFFFFFFF))

#endif // BITMANIP_H