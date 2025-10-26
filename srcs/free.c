#include "malloc.h"
#include "allocations.h"
#include "multithreading.h"
#include "libft.h"

static bool free_in_block(t_allocs_block *block, void *ptr)
{
	for (ssize_t i = ALLOCS_COUNT - 1; i >= 0; --i)
	{
		if (block->allocs[i].ptr == ptr)
		{
			// Defragement
			ft_memmove(
				&(block->allocs[i]),
				&(block->allocs[i + 1]),
				(ALLOCS_COUNT - i - 1) * sizeof(t_alloc)
			);
			ft_bzero(&(block->allocs[ALLOCS_COUNT - 1]), sizeof(t_alloc));

			return true;
		}
	}
	return false;
}

static bool	free_in_blocks(t_allocs_block *blocks, size_t count, size_t bsize, void *ptr)
{
	for (ssize_t i = count - 1; i >= 0; --i)
	{
		if (blocks[i].ptr && blocks[i].ptr <= ptr && blocks[i].ptr + bsize >= ptr)
			return free_in_block(&(blocks[i]), ptr);
	}
	return false;
}

static void	freeup_blocks(t_allocs_block *blocks, size_t count, size_t bsize)
{
	// Don't even keep a mmap zone if no malloc
	for (size_t i = 0; i < count; ++i)
	{
		if (blocks[i].ptr && !blocks[i].allocs[0].ptr)
		{
			munmap(blocks[i].ptr, bsize);
			blocks[i].ptr = 0;
		}
	}
}

void free(void *ptr)
{
	if (!ptr)
		return ;

	malloc_lock_mutex();
	if (free_in_blocks(blocks_g.tiny_blocks, TINY_BLOCKS_COUNT, TINY_BLOCK_SIZE, ptr))
		freeup_blocks(blocks_g.tiny_blocks, TINY_BLOCKS_COUNT, TINY_BLOCK_SIZE);
	else if (free_in_blocks(blocks_g.small_blocks, SMALL_BLOCKS_COUNT, SMALL_BLOCK_SIZE, ptr))
		freeup_blocks(blocks_g.tiny_blocks, SMALL_BLOCKS_COUNT, SMALL_BLOCK_SIZE);
	else if (free_in_blocks(blocks_g.big_blocks, BIG_BLOCKS_COUNT, 0, ptr))
		freeup_blocks(blocks_g.tiny_blocks, BIG_BLOCKS_COUNT, 0);
	else
	{
		// Double free
	}
	malloc_unlock_mutex();
}
