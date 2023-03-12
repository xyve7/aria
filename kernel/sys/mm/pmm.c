#include <sys/mm/pmm.h>

static volatile struct limine_memmap_request memmap_request = {
	.id = LIMINE_MEMMAP_REQUEST,
	.revision = 0
};
static volatile struct limine_hhdm_request hhdm_request = {
	.id = LIMINE_HHDM_REQUEST,
	.revision = 0
};

static u8* pmm_bitmap = NULL;
static u64 pmm_bitmap_size = 0;
static u64 pmm_highest_addr = 0;
static u64 pmm_highest_page = 0;

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
	pmm_highest_page = pmm_highest_addr / page_size; 
	pmm_bitmap_size = ALIGN_UP(pmm_highest_page / 8, page_size);

	printf("pmm_bitmap size=%lu\n", pmm_bitmap_size);

	/* Iterates through the entire memory map entry array again, finding a hole big enough to store the bitmap */
	for (size_t i = 0; i < pmm_entry_count; i++) {
		if(pmm_entries[i]->type == LIMINE_MEMMAP_USABLE) {
			if(pmm_entries[i]->length >= pmm_bitmap_size) {
				/* Gets a pointer to some free memory */
				pmm_bitmap = (u8*)(pmm_entries[i]->base + hhdm_request.response->offset);

				/* Sets the entire bitmap as used */
				memset(pmm_bitmap, 0xFF, pmm_bitmap_size);

				/* Subtracts the length of the bitmap size */
				pmm_entries[i]->length -= pmm_bitmap_size;
				/* Makes sure the base is not in range of the bitmap */
				pmm_entries[i]->base += pmm_bitmap_size;
			}
		}
	}

	for (size_t i = 0; i < pmm_entry_count; i++) {
		if(pmm_entries[i]->type == LIMINE_MEMMAP_USABLE) {
			for (size_t j = pmm_entries[i]->base; j < pmm_entries[i]->length; j+=page_size) {
				/* Clears the usable entries */
				bitmap_clear(pmm_bitmap, j / page_size);
			}	
		}
	}
		
}

void* pmm_find_contigious(u64 pages) {
	u64 index = 0;
	while(index <= pmm_highest_page) {
		if(!bitmap_get(pmm_bitmap, index)) {
			size_t i = 0; 
			for(i = index; i < (index + pages) && !bitmap_get(pmm_bitmap, i); i++) {
			}
			if(i == (index + pages - 1)){
				return (void*)(index * page_size);
			}
		}
	}
	return NULL;
}

void* pmm_alloc(u64 pages) {
	u64 index = 0;
	while(index <= pmm_highest_page) {
		if(!bitmap_get(pmm_bitmap, index)) {
			printf("%lu\n", index);
			printf("%lu\n", index * page_size);
			bitmap_set(pmm_bitmap, index);
			return (void*)(index * page_size);
		}
		index++;
	}
	return NULL;
}
void pmm_free(void* address, u64 pages) {
	u64 index = (u64)address;
	index /= page_size;
	for(size_t i = index; i < (index + pages); i++) {
		bitmap_clear(pmm_bitmap, i);
	}
}
