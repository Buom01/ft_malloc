#include "libft_malloc.h"
#include "allocations.h"
#include "libft.h"

static bool free_in_block(t_allocs_block *block, void *ptr)
{
	for (ssize_t i = ALLOCS_COUNT - 1; i >= 0; --i)
	{
		if (block->allocs[i].ptr == ptr)
		{
			ft_memmove(
				&(block->allocs[i]),
				&(block->allocs[i + 1]),
				(ALLOCS_COUNT - i - 1) * sizeof(t_allocs_block)
			);
			ft_bzero(&(block->allocs[ALLOCS_COUNT - 1]), sizeof(t_allocs_block));

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

static void	defrag_blocks(t_allocs_block *blocks, size_t count, size_t bsize)
{
	// @TODO
	(void)blocks;
	(void)count;
	(void)bsize;
}

void free(void *ptr)
{
	if (!ptr)
		return ;

	t_allocs_blocks	*blocks = get_blocks();

	if (free_in_blocks(blocks->tiny_blocks, TINY_BLOCKS_COUNT, TINY_BLOCK_SIZE, ptr))
		defrag_blocks(blocks->tiny_blocks, TINY_BLOCKS_COUNT, TINY_BLOCK_SIZE);
	else if (free_in_blocks(blocks->small_blocks, SMALL_BLOCKS_COUNT, SMALL_BLOCK_SIZE, ptr))
		defrag_blocks(blocks->tiny_blocks, SMALL_BLOCKS_COUNT, SMALL_BLOCK_SIZE);
	else if (free_in_blocks(blocks->big_blocks, BIG_BLOCKS_COUNT, 0, ptr))
		defrag_blocks(blocks->tiny_blocks, BIG_BLOCKS_COUNT, 0);
	else
		printf("WARNING : Failed to freeup %p\n", ptr);
}
