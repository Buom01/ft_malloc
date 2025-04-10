#ifndef ALLOCATIONS_H
# define ALLOCATIONS_H

# include "libft_malloc.h"

# define ALLOCS_COUNT 128
# define TINY_ALLOC_SIZE 16 // n
# define SMALL_ALLOC_SIZE 128 // m
# define TINY_BLOCK_SIZE ALLOCS_COUNT // N 
# define SMALL_BLOCK_SIZE TINY_ALLOC_SIZE * ALLOCS_COUNT // M
# define TINY_BLOCKS_COUNT 1024
# define SMALL_BLOCKS_COUNT 1024
# define BIG_BLOCKS_COUNT 1024 * ALLOCS_COUNT

typedef struct s_alloc
{
	void	*ptr;
	size_t	len;	
} t_alloc;

typedef struct s_allocs_block
{
	void		*ptr;
	t_alloc		allocs[ALLOCS_COUNT];
} t_allocs_block;

typedef struct s_allocs_blocks
{
	t_allocs_block	tiny_blocks[TINY_BLOCKS_COUNT];
	t_allocs_block	small_blocks[SMALL_BLOCKS_COUNT];
	t_alloc			big_blocks[BIG_BLOCKS_COUNT];
} t_allocs_blocks;

t_allocs_blocks	get_blocks();

#endif
