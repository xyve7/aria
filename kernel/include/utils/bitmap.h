#ifndef BITMAP_H
#define BITMAP_H

#include <bitmanip.h>
#include <kernel.h>

typedef struct {
	u8* data;
	size_t size;
} bitmap;

bool bitmap_get(bitmap* bm, size_t index);
void bitmap_set(bitmap* bm, size_t index);
void bitmap_clear(bitmap* bm, size_t index);

#endif/* BITMAP_H */
