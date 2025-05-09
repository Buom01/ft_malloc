#include "libft_malloc.h"
#include "allocations.h"
#include "multithreading.h"
#include "system.h"
#include "libft.h"

static void	*insert_alloc(t_allocs_block *block, void *ptr, size_t size, size_t index)
{
	if (block->allocs[index].ptr)
	{
		// Keeping ordered
		ft_memmove(
			&(block->allocs[index + 1]),
			&(block->allocs[index]),
			(ALLOCS_COUNT - index - 1) * sizeof(t_alloc)
		);
	}

	block->allocs[index].ptr = ptr;
	block->allocs[index].len = size;

	return ptr;
}

static void	*get_available_in_block(t_allocs_block *block, size_t bsize, size_t size)
{
	// case 0 : all allocations of the block are taken
	if (block->allocs[ALLOCS_COUNT - 1].ptr)
		return NULL;

	for (size_t i = 0; i < ALLOCS_COUNT; ++i)
	{
		// The allocation is used
		if (block->allocs[i].ptr)
		{
			// case 1 : there are space between our first allocation and the block's begin
			if (i == 0)
			{
				if (block->allocs[i].ptr - block->ptr >= (ssize_t)size)
					return insert_alloc(block, block->ptr, size, i);
			}
			// case 2 : there are space between two allocations
			else
			{
				if (block->allocs[i].ptr - block->allocs[i - 1].ptr - block->allocs[i - 1].len >= size)
					return insert_alloc(block, block->allocs[i - 1].ptr + block->allocs[i -1].len, size, i);
			}
		}
		// case 3 : the block is empty
		else if (i == 0)
		{
			return insert_alloc(block, block->ptr, size, 0);
		}
		// case 4 : there are space between the last allocation and the block's end
		else if (block->ptr + (ssize_t)bsize - block->allocs[i - 1].ptr - block->allocs[i - 1].len >= size)
		{
			return insert_alloc(block, block->allocs[i - 1].ptr + block->allocs[i - 1].len, size, i);
		}
		// case 5 : there are not space
		else
			break ;
	}

	return NULL;
}

static void	*get_available(t_allocs_block *blocks, size_t count, size_t bsize, size_t size)
{
	void	*ptr	= NULL;

	for (size_t i = 0; i < count; ++i)
	{
		if (blocks[i].ptr)
		{
			if ((ptr = get_available_in_block(&(blocks[i]), bsize, size)))
				return ptr;
		}
		else
			break ;
	}

	return NULL;
}

static void	*get_new_block_alloc(t_allocs_block *blocks, size_t count, size_t bsize, size_t size)
{
	for (size_t i = 0; i < count; ++i)
	{
		if (!blocks[i].ptr)
		{
			blocks[i].ptr = mmap(NULL, bsize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
			if (!blocks[i].ptr)
				return NULL;
			blocks[i].allocs[0].ptr = blocks[i].ptr;
			blocks[i].allocs[0].len = size;
			return blocks[i].ptr;
		}
	}

	return NULL;
}

static void	*get_alloc(t_allocs_block *blocks, size_t count, size_t bsize, size_t size)
{
	void	*ptr	= NULL;

	malloc_lock_mutex();
	if (bsize && (ptr = get_available(blocks, count, bsize, size)))
	{
		malloc_unlock_mutex();
		return ptr;
	}
	else if ((ptr = get_new_block_alloc(blocks, count, bsize > 0 ? bsize : size, size)))
	{
		malloc_unlock_mutex();
		return ptr;
	}
	else
	{
		malloc_unlock_mutex();
		return NULL;
	}
}

void	*malloc(size_t size)
{
	size = ALIGN(size);

	if (size <= TINY_ALLOC_SIZE)
		return get_alloc(blocks_g.tiny_blocks, TINY_BLOCKS_COUNT, TINY_BLOCK_SIZE, size);
	else if (size <= SMALL_ALLOC_SIZE)
		return get_alloc(blocks_g.small_blocks, SMALL_BLOCKS_COUNT, SMALL_BLOCK_SIZE, size);
	else if (size <= get_malloc_limit())
		return get_alloc(blocks_g.big_blocks, BIG_BLOCKS_COUNT, 0, size);
	else
		return NULL;	
}

