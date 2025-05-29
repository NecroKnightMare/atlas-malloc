#include "malloc.h"
#include <unistd.h>

void _free(void *ptr) {
    if (ptr == NULL) {
        return; // Avoid freeing a null pointer
    }
    heap_t *header = (heap_t *)((char *)ptr - sizeof(heap_t));

   /*look at malloc free repo again and use your SLL*/
    header->size = 1; 
}
// int main (void)
// {
//     void *ptr = malloc(100); // Allocate 100 bytes of memory
//     printf("Allocated memory at: %p\n", ptr);

//     _free(ptr); // Free the allocated memory
//     printf("Memory freed.\n");

//     return 0;
// }