#include "malloc.h"
#include "allocations.h"
#include "multithreading.h"
#include "libft.h"

void	*calloc(size_t n, size_t size)
{
    void    *ptr;

    ptr = malloc(n*size);
    if (ptr)
        ft_bzero(ptr, n*size);

    return ptr;
}