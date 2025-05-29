# ifndef _MALLOC_H
# define _MALLOC_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>

/*allocate alignment for pages size*/
#define ALIGN(size, alignment) (((size) + (alignment - 1)) & ~(alignment - 1))/*malloc*/
#define align(offset, align) ((offset + (align - 1)) & -align)/*naive malloc*/

typedef struct heap_size
{
	size_t size; /*needed for allocation*/
	size_t *prev; /*pointer to previous size*/
} heap_t;

typedef struct block_meta
{
	size_t size; /*size of the block*/
	struct block_meta *next; /*pointer to next block*/
} block_meta_t;


void _header(char *chunk, size_t chunk_size, size_t *excess_mem);/*naive malloc*/
void *_unused(char *heap_start, size_t call_nb);/*naive malloc*/
void *extend(size_t chunk_size, size_t *excess_mem);/*naive malloc*/
void *naive_malloc(size_t size); /*task 0*/
void *_malloc(size_t size); /*task 1*/
void _free(void *ptr); /*task 2*/

#endif /* _MALLOC_H */
