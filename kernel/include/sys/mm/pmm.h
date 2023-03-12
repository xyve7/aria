#ifndef PMM_H
#define PMM_H

#include <utils/bitmap.h>
#include <libc/string.h>
#include <libc/stdio.h>

void pmm_init(void);
void* pmm_alloc(u64 pages);
void pmm_free(void* address, u64 pages);

#endif/* PMM_H */
