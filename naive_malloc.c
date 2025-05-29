#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#include "malloc.h"


/**
 * _header - set chunk headers
 * @chunk: pointer to start of chunk
 * @chunk_size: chunk size
 * @overflow: pointer to excess memory
 */
void _header(char *chunk, size_t chunk_size, size_t *overflow)
{
	*overflow -= chunk_size;
	*(size_t *)chunk = chunk_size;
	*(size_t *)(chunk + *(size_t *)chunk) = *overflow;
}

/**
 * empty_space - find unused chunk block
 * @heap_start: pointer to heap start
 * @call_count: specifies how many times malloc has been called
 *
 * Return: pointer to start of unused chunk
 */
void *empty_space(char *heap_start, size_t call_count)
{
	while (call_count > 0)
	{
		heap_start += *(size_t *)heap_start;
		--call_count;
	}
	return (heap_start);
}

/**
 * req_memory - calls sbrk with size aligned to page size
 * @chunk_size: aligned size request
 * @overflow: pointer to excess memory
 *
 * Return: pointer to start of new chunk, NULL on failure
 */
void *req_memory(size_t chunk_size, size_t *overflow)
{
	void *chunk;

	chunk = sbrk(align(chunk_size, sysconf(_SC_PAGESIZE)));
	if (chunk == (void *) -1)
		return (NULL);
	*overflow += align(chunk_size, sysconf(_SC_PAGESIZE));
	return (chunk);
}

/**
 * naive_malloc - naive malloc: dynamically allocates memory to the heap
 * @size: number of bytes to allocate
 *
 * Return: the memory address newly allocated, or NULL on error
 */
void *naive_malloc(size_t size)
{
	void *chunk;
	static void *heap_start;
	static size_t call_count;
	size_t hdr_size, chunk_size, overflow;

	hdr_size = sizeof(size_t);
	chunk_size = align(size, sizeof(void *)) + hdr_size;
	if (!heap_start)
	{
		overflow = 0;
		heap_start = chunk = req_memory(chunk_size, &overflow);
		if (!chunk)
			return (NULL);
	}
	else
	{
		chunk = empty_space(heap_start, call_count);
		overflow = *(size_t *)chunk;
		if (overflow < chunk_size + hdr_size)
			if (!req_memory(chunk_size, &overflow))
				return (NULL);
	}
	_header(chunk, chunk_size, &overflow);
	++call_count;
	return ((char *)chunk + hdr_size);
}
int main(void)
{
    void *ptr = naive_malloc(100);
    printf("Allocated memory at: %p\n", ptr);
    return 0;
}
