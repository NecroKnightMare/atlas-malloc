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

void *_malloc(size_t size)
{
	size_t pagesize = sysconf(_SC_PAGESIZE);
	size_t total_size = ALIGN(size + sizeof(heap_t), pagesize);
	void *ptr = sbrk(total_size);

	if (ptr == (void *)-1)
	{
		return (NULL);
	}
	/* Store metadata in heap header */
	heap_t *header = (heap_t *)ptr;
	header->size = total_size;

	/* Return pointer to user memory (after heap header) */
	return ((void *)((char *)header + sizeof(heap_t)));
}
// int main(void)
// {
// 	void *ptr = _malloc(100);
// 	printf("Allocated memory at: %p\n", ptr);
// 	return 0;
// }
