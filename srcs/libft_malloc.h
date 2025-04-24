#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/mman.h>

void free(void *ptr);
void *ft_malloc(size_t size);
void *realloc(void *ptr, size_t size);

void show_alloc_mem();

char *ft_ptrtoa_noalloc(void *ptr);
void ft_putptr_fd_noalloc(void *ptr, int fd);
char *ft_itoa_noalloc(int n);
void ft_putnbr_fd_noalloc(int n, int fd);

#endif
