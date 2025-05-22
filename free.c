#include "malloc.h"
#include <stdlib.h>

void _free(void *ptr) {
    if (ptr == NULL) {
        return; // Avoid freeing a null pointer
    }
    heap_t *header = (heap_t *)((char *)ptr - sizeof(heap_t));

    free(ptr); // Use the standard free function to release memory
}
// int main (void)
// {
//     void *ptr = malloc(100); // Allocate 100 bytes of memory
//     printf("Allocated memory at: %p\n", ptr);

//     _free(ptr); // Free the allocated memory
//     printf("Memory freed.\n");

//     return 0;
// }