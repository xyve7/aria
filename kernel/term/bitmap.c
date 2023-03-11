#include <utils/bitmap.h>

bool bitmap_get(bitmap* bm, size_t index) {
	return bit_get(bm->data[index / 8], index % 8);
}
void bitmap_set(bitmap* bm, size_t index) {
	bit_set(bm->data[index / 8], index % 8);
}
void bitmap_clear(bitmap* bm, size_t index) {
	bit_clear(bm->data[index / 8], index % 8);
}