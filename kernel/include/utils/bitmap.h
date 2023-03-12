#ifndef BITMAP_H
#define BITMAP_H

#include <kernel.h>
#include <bitmanip.h>

static inline void bitmap_clear(u8* bitmap, u64 index) {
	bit_clear(bitmap[index / 8], index % 8);	
}
static inline void bitmap_set(u8* bitmap, u64 index) {
	bit_set(bitmap[index / 8], index % 8);	
}
static inline bool bitmap_get(u8* bitmap, u64 index) {
	bit_get(bitmap[index / 8], index % 8);	
}

#endif
