#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include "malloc.h"

/**
 * naive_malloc - Allocates memory using sbrk with alignment
 * @size: Size of memory requested
 *
 * Description: This function allocates memory by extending the program break
 * Return: Pointer to allocated memory or NULL on failure
**/

heap_t *free_list = NULL;


void *naive_malloc(size_t size) {
    size_t total_size = ALIGN(size + sizeof(heap_t), sysconf(_SC_PAGESIZE));

    // Traverse the free list to find a suitable chunk
    heap_t *current = free_list;
    while (current) {
        if (current->is_free && current->size >= total_size) {
            current->is_free = 0;
            return (void *)((char *)current + sizeof(heap_t));
        }
        current = current->next;
    }

    // Allocate new memory if no free block exists
    void *ptr = sbrk(total_size);
    if (ptr == (void *)-1) return NULL;

    heap_t *header = (heap_t *)ptr;
    header->size = total_size;
    header->is_free = 0;
    header->next = free_list;
    free_list = header;

    return (void *)((char *)header + sizeof(heap_t));
}

// void *naive_malloc(size_t size)
// {
// 	size_t pagesize = sysconf(_SC_PAGESIZE);
// 	size_t total_size = ALIGN(size + sizeof(heap_t), pagesize);
// 	void *ptr = sbrk(total_size);

// 	if (ptr == (void *)-1)
// 	{
// 		return NULL;
// 	}
// 	/* Store metadata in heap header */
// 	heap_t *header = (heap_t *)ptr;
// 	header->size = total_size;

// 	/* Return pointer to user memory (after heap header) */
// 	return (void *)((char *)header + sizeof(heap_t));
// }

// int main(void)
// {
// 	void *ptr = naive_malloc(100);
// 	printf("Allocated memory at: %p\n", ptr);
// 	return 0;
// }
