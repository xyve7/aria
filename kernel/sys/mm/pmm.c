#include <sys/mm/pmm.h>
/**
 * This is probably one of this things that took me ages to understand at first, but it makes sense.
 * 
 * Essentially, we are using a bitmap to keep track of the system's free and used memory.
 * 
 * Each bit in the bitmap represents a page, 1 being used and 0 being free.
 * 
 * The index of the bitmap is essentially the address, well kinda.
 * 
 * To get the address from the index, it's index * page_size, since the bitmap keeps track of each page, so getting the address would be a matter of multiplication.
 * You would add hhdm offset to get the virtual address.
 * 
 * 
*/
static volatile struct limine_memmap_request memmap_request = {
	.id = LIMINE_MEMMAP_REQUEST,
	.revision = 0
};
static volatile struct limine_hhdm_request hhdm_request = {
	.id = LIMINE_HHDM_REQUEST,
	.revision = 0
};

const char* limine_entry_str[] = {
	"LIMINE_MEMMAP_USABLE",
	"LIMINE_MEMMAP_RESERVED",
	"LIMINE_MEMMAP_ACPI_RECLAIMABLE",
	"LIMINE_MEMMAP_ACPI_NVS",
	"LIMINE_MEMMAP_BAD_MEMORY",
	"LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE",
	"LIMINE_MEMMAP_KERNEL_AND_MODULES",
	"LIMINE_MEMMAP_FRAMEBUFFER"
};

static u8* pmm_bitmap = NULL;
static u64 pmm_bitmap_size = 0;
static u64 pmm_highest_addr = 0;
static u64 pmm_highest_page = 0;
static u64 pmm_last_alloc = 0;

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
		printf("base=%p,length=%p,type=%s\n", pmm_entries[i]->base, pmm_entries[i]->length, limine_entry_str[pmm_entries[i]->type]);
	}
	/* Aligns the size of the bitmap based on page size */
	pmm_highest_page = pmm_highest_addr / page_size;
	pmm_bitmap_size = ALIGN_UP(pmm_highest_page / 8, page_size);

	printf("pmm_bitmap_size=%lu\n", pmm_bitmap_size);

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

				break;
			}
		}
	}

	for (size_t i = 0; i < pmm_entry_count; i++) {
		if(pmm_entries[i]->type == LIMINE_MEMMAP_USABLE) {
			for (size_t j = pmm_entries[i]->base; j < pmm_entries[i]->length; j+=page_size) {
				/* Gets the index */
				size_t index = j / page_size;
				/* Clears the usable entries */
				bitmap_clear(pmm_bitmap, index);
			}
		}
	}

}

void* pmm_find_contigious(u64 pages) {
	u64 index = pmm_last_alloc;
	size_t i = index;
	/* Iterates through the entire bitmap, finding a contiguous block */
	for(i; (i < pmm_highest_page) && (i < (index + pages)) && !bitmap_get(pmm_bitmap, i); i++) {

	}
	/* Checks if it found one */
	if(i == (index + pages)) {
		/* make sure to mark the entire range of pages to used*/
		bitmap_set(pmm_bitmap, index);
		/* Offsets the last allocation by the size, so it doesn't have to iterate through the known used pages */
		pmm_last_alloc = index + pages;
		return (void*)(index * page_size);
	}
	return NULL;
}

void* pmm_alloc(u64 pages) {
	void* address = pmm_find_contigious(pages);
	if(address == NULL) 
		;
	return address;
}
void pmm_free(void* address, u64 pages) {
	u64 index = (u64)address;
	index /= page_size;
	for(size_t i = index; i < (index + pages); i++) {
		bitmap_clear(pmm_bitmap, i);
	}
	/* The next alloc is going to be faster */
	pmm_last_alloc = index;
}
