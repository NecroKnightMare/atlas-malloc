#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * main - Extends the program break and stores a character
 * 
 * Return: EXIT_SUCCESS
 */


int main(void)
{
    void *initial_break, *new_break;
    char *storage;

    /* Get the current break */
    initial_break = sbrk(0);
    printf("Starting break is %p\n", initial_break);

    /* Extend the break by 1 byte */
    new_break = sbrk(1);
    if (new_break == (void *)-1)
    {
        perror("sbrk");
        return (EXIT_FAILURE);
    }
    
    printf("Break after extension is %p\n", sbrk(0));

    /* Store and retrieve character */
    storage = (char *)initial_break;
    *storage = 'H';
    printf("Address of our char is %p\n", (void *)storage);
    printf("Value at this address is '%c'\n", *storage);

    return (EXIT_SUCCESS);
}

