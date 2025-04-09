#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/mman.h>

# include "libft.h"
# include "allocations.h"

// Public
void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);

void show_alloc_mem();

// Internal
void ft_putptr_fd(void *ptr, int fd);
char *ft_ptrtoa(void *ptr);

#endif
