#ifndef BITMANIP_H
#define BITMANIP_H

#include <kernel.h>
/**
 * @brief Macros for extracting parts of a bit
 * 
 * This is made for convenience.
 * 
 * @note These work with all unsigned numbers, however, it assumes you know the size of the number and dont do byte_2 on a 16 bit number or anything
 * 
 */
#define byte_0(x) ((u8)((x) & 0xFF))
#define byte_1(x) ((u8)(((x) >> 8) & 0xFF))
#define byte_2(x) ((u8)(((x) >> 16) & 0xFF))
#define byte_3(x) ((u8)(((x) >> 24) & 0xFF))
#define byte_4(x) ((u8)(((x) >> 32) & 0xFF))
#define byte_5(x) ((u8)(((x) >> 40) & 0xFF))
#define byte_6(x) ((u8)(((x) >> 48) & 0xFF))
#define byte_7(x) ((u8)(((x) >> 56) & 0xFF))

#define word_0(x) ((u16)((x) & 0xFFFF))
#define word_1(x) ((u16)(((x) >> 16) & 0xFFFF))
#define word_2(x) ((u16)(((x) >> 32) & 0xFFFF))
#define word_3(x) ((u16)(((x) >> 48) & 0xFFFF))

#define dword_0(x) ((u32)((x) & 0xFFFFFFFF))
#define dword_1(x) ((u32)(((x) >> 32) & 0xFFFFFFFF))

/**
 * @brief Macros for setting/clearing a bit
 * 
 * This is made for convenience.
 * 
 */
#define bit_set(byte, bit) ((byte) |= (1 << (bit)))
#define bit_clear(byte, bit) ((byte) &= ~(1 << (bit)))
#define bit_get(byte, bit) ((byte) & (1 << (bit)))


#endif/* BITMANIP_H */
