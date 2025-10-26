#ifndef ALLOCATIONS_H
# define ALLOCATIONS_H

# include "malloc.h"

# define ALLOCS_COUNT 128
# define TINY_ALLOC_SIZE 128 // n
# define SMALL_ALLOC_SIZE 2048 // m
# define TINY_BLOCK_SIZE (sysconf(_SC_PAGESIZE)) * 10 // N
# define SMALL_BLOCK_SIZE (sysconf(_SC_PAGESIZE) * 500) // M
# define TINY_BLOCKS_COUNT 1024
# define SMALL_BLOCKS_COUNT 1024
# define BIG_BLOCKS_COUNT 1024 * ALLOCS_COUNT

# define ALIGNEMENT 16
# define ALIGN(size) (((size) + (ALIGNEMENT - 1)) & ~(ALIGNEMENT - 1));

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
	t_allocs_block	big_blocks[BIG_BLOCKS_COUNT];
} t_allocs_blocks;

extern t_allocs_blocks	blocks_g;

#endif
