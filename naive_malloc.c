#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include "malloc.h"

void *naive_malloc(size_t size)
{
    size_t pagesize = sysconf(_SC_PAGESIZE);
    size_t total_size = ALIGN(size + sizeof(heap_t), pagesize);
    void *ptr = sbrk(total_size);

    if (ptr == (void *)-1)
        return NULL;

    /* Store metadata in heap header */
    heap_t *header = (heap_t *)ptr;
    header->size = total_size;

    /* Return pointer to user memory (after heap header) */
    /*return (void *)(header + 1);*/
    return (void *)((char *)header + sizeof(heap_t));
}

//  int main(void)
//  {
//      void *ptr = naive_malloc(100);
//     printf("Allocated memory at: %p\n", ptr);
//    return 0;
// }
