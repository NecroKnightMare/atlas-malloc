# ifndef _MALLOC_H
# define _MALLOC_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>

/*allocate alignment for pages size*/
#define ALIGN(size, alignment) (((size) + (alignment - 1)) & ~(alignment - 1))

typedef struct heap_size
{
	size_t size; /*needed for allocation*/
	/*struct heap_size *next; next memory allocation*/
} heap_t;


void *naive_malloc(size_t size); /*task 0*/
/*void *_malloc(size_t size); task 1*/
/* void _free(void *ptr); task 2*/

#endif /* _MALLOC_H */