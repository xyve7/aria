#include <sys/mm/pmm.h>

static volatile struct limine_memmap_request memmap_request = {
	.id = LIMINE_MEMMAP_REQUEST,
	.revision = 0
};

static bitmap pmm_bitmap;
static u64 pmm_highest_addr = 0;

void pmm_init(void) {
	struct limine_memmap_entry ** pmm_entries = memmap_request.response->entries;
	u64 pmm_entry_count = memmap_request.response->entry_count;

	/* Iterates through the entire memory map entry array, determining what the highest address is (also the size of the bitmap) */
	for (size_t i = 0; i < pmm_entry_count; i++) {
		if(pmm_entries[i]->type == LIMINE_MEMMAP_USABLE) {
			/* Obtains the ending address of the range */
			u64 limit = pmm_entries[i]->base + pmm_entries[i]->length;
			/* Compares them and sets the new max if larger */
			if(limit > pmm_highest_addr)
				pmm_highest_addr = limit;
		}
	}
	/* Aligns the size of the bitmap based on page size */
	pmm_bitmap.size = ALIGN_UP(pmm_highest_addr / page_size / 8, page_size);

	printf("pmm_bitmap.size=%lu\n", pmm_bitmap.size);

	/* Iterates through the entire memory map entry array again, finding a hole big enough to store the bitmap */
	for (size_t i = 0; i < pmm_entry_count; i++) {
		if(pmm_entries[i]->type == LIMINE_MEMMAP_USABLE) {
			if(pmm_entries[i]->length >= pmm_bitmap.size) {
				/* Gets a pointer to some free memory */
				pmm_bitmap.data = (u8*)(pmm_entries[i]->base + hhdm_request.response->offset);

				/* Sets the entire bitmap as used */
				memset(pmm_bitmap.data, 0xFF, pmm_bitmap.size);

				/* Subtracts the length of the bitmap size */
				pmm_entries[i]->length -= pmm_bitmap.size;
				/* Makes sure the base is not in range of the bitmap */
				pmm_entries[i]->base += pmm_bitmap.size;
			}
		}
	}

	for (size_t i = 0; i < pmm_entry_count; i++) {
		if(pmm_entries[i]->type == LIMINE_MEMMAP_USABLE) {
			for (size_t j = pmm_entries[i]->base; j < pmm_entries[i]->length; j+=page_size) {
				/* Clears the usable entries */
				bitmap_clear(&pmm_bitmap, j / page_size);
			}	
		}
	}
		
}