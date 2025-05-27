#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include "malloc.h"

/**
 * _malloc - Allocates memory using sbrk with alignment
 * @size: Size of memory requested
 *
 * Description: This function allocates memory by extending the program break
 * Return: Pointer to allocated memory or NULL on failure
**/
heap_t *free_list = NULL;

void *_malloc(size_t size)
{
	size_t pagesize = sysconf(_SC_PAGESIZE);
	size_t total_size = ALIGN(size + sizeof(heap_t), pagesize);
	// void *ptr = sbrk(total_size);
	heap_t *current = free_list;

	    while (current) {
        if (current->is_free && current->size >= total_size) {
            current->is_free = 0;
            return (void *)((char *)current + sizeof(heap_t));
        }
        current = current->next;
    }

    // If no suitable block is found, allocate new memory
    void *ptr = sbrk(total_size);
    if (ptr == (void *)-1) return NULL;

    heap_t *header = (heap_t *)ptr;
    header->size = total_size;
    header->is_free = 0;
    header->next = NULL;

    return (void *)((char *)header + sizeof(heap_t));
}


// 	if (ptr == (void *)-1)
// 	{
// 		return (NULL);
// 	}
// 	/* Store metadata in heap header */
// 	heap_t *header = (heap_t *)ptr;
// 	header->size = total_size;

// 	/* Return pointer to user memory (after heap header) */
// 	return ((void *)((char *)header + sizeof(heap_t)));
// }

// int main(void)
// {
// 	void *ptr = _malloc(100);
// 	printf("Allocated memory at: %p\n", ptr);
// 	return 0;
// }
