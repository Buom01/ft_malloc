#include "libft_malloc.h"

//sysconf(_SC_PAGESIZE)

static void	*insert_alloc(t_allocs_block block, void *ptr, size_t size, size_t index)
{
	if (block.allocs[index].ptr)
	{
		memmove(
			block.allocs + (index + 1) * sizeof(t_allocs_block),
			block.allocs + index * sizeof(t_allocs_block),
			(ALLOCS_COUNT - index - 1) * sizeof(t_allocs_block)
		);
	}

	block.allocs[index].ptr = ptr;
	block.allocs[index].len = size;

	return ptr;
}

static void	*get_available_in_block(t_allocs_block block, size_t bsize, size_t size)
{
	if (block.allocs[ALLOCS_COUNT - 1].ptr)
		return NULL;

	for (size_t i = 0; i <= ALLOCS_COUNT; ++i)
	{
		if (block.allocs[i].ptr)
		{
			if (i == 0)
			{
				if ((size_t)block.allocs[i].ptr - (size_t)block.ptr >= size)
					return insert_alloc(block, block.ptr, size, i);
			}
			else if (i == ALLOCS_COUNT)
			{
				if ((size_t)block.ptr + bsize - (size_t)block.allocs[i].ptr - block.allocs[i].len >= size)
					return insert_alloc(block, block.allocs[i].ptr + block.allocs[i].len, size, i);
			}
			else
			{
				if ((size_t)block.allocs[i].ptr - (size_t)block.allocs[i - 1].ptr - (size_t)block.allocs[i - 1].len >= size)
					return insert_alloc(block, block.allocs[i - 1].ptr + block.allocs[i -1].len, size, i);
			}
		}
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
			if ((ptr = get_available_in_block(blocks[i], bsize, size)))
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

	if ((ptr = get_available(blocks, count, bsize, size)))
		return ptr;
	if ((ptr = get_new_block_alloc(blocks, count, bsize, size)))
		return ptr;
	return NULL;
}

void	*malloc(size_t size)
{
	t_allocs_blocks	blocks = get_blocks();

	if (size <= TINY_ALLOC_SIZE)
		return get_alloc(blocks.tiny_blocks, TINY_BLOCKS_COUNT, TINY_BLOCK_SIZE, size);
	else if (size <= SMALL_ALLOC_SIZE)
		return get_alloc(blocks.small_blocks, SMALL_BLOCKS_COUNT, SMALL_BLOCK_SIZE, size);

	return NULL;	
}

