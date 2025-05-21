#include <unistd.h>
#include <stddef.h>

/**
 * naive_malloc - Allocates memory by extending the program break
 * @size: Number of bytes to allocate
 * 
 * Return: Pointer to allocated memory, or NULL on failure
 */
void *naive_malloc(size_t size)
{
    void *ptr;

    ptr = sbrk(size);
    if (ptr == (void *)-1)
        return (NULL);

    return ptr;
}
