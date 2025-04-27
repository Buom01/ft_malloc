#include "libft_malloc.h"
#include "allocations.h"
#include "multithreading.h"
#include "system.h"
#include "libft.h"

typedef struct s_alloc_info
{
    t_allocs_block  *block;
    size_t          index;
    size_t          bsize;
} t_alloc_info;

static void find_alloc_in_block(t_allocs_block *block, size_t bsize, void *ptr, t_alloc_info *alloc)
{
	for (ssize_t i = ALLOCS_COUNT - 1; i >= 0; --i)
	{
		if (block->allocs[i].ptr == ptr)
		{
            alloc->block = block;
            alloc->bsize = bsize;
            alloc->index = i;
            break ;
		}
	}
}

static void	find_alloc_in_blocks(t_allocs_block *blocks, size_t count, size_t bsize, void *ptr, t_alloc_info *alloc)
{
	for (ssize_t i = count - 1; i >= 0; --i)
	{
		if (blocks[i].ptr && blocks[i].ptr <= ptr && blocks[i].ptr + bsize >= ptr)
        {
			find_alloc_in_block(&(blocks[i]), bsize, ptr, alloc);
            break;
        }
	}
}

static void find_alloc(void *ptr, t_alloc_info *alloc)
{

	if (!ptr)
		return;

    find_alloc_in_blocks(blocks_g.tiny_blocks, TINY_BLOCKS_COUNT, TINY_BLOCK_SIZE, ptr, alloc);
    if (alloc->block)
        return ;
    find_alloc_in_blocks(blocks_g.small_blocks, SMALL_BLOCKS_COUNT, SMALL_BLOCK_SIZE, ptr, alloc);
    if (alloc->block)
        return ;
    find_alloc_in_blocks(blocks_g.big_blocks, BIG_BLOCKS_COUNT, 0, ptr, alloc);
}


void	*realloc(void *ptr, size_t size)
{
    t_alloc_info    alloc = {0};

    size = ALIGN(size);

    if (size <= 0)
    {
        if (ptr)
            free(ptr);
        return NULL;
    }
    else if (size > get_malloc_limit())
        return NULL;

    malloc_lock_mutex();
    find_alloc(ptr, &alloc);

    if (alloc.block)
    {
        // Case 0 : The new allocation is smaller (or equal)
        if (alloc.block->allocs[alloc.index].len >= size)
        {
            alloc.block->allocs[alloc.index].len = size;
            malloc_unlock_mutex();
            return ptr;
        }
        // Case 1 : The block is full and the alloc is the last
        else if (alloc.index == ALLOCS_COUNT - 1 &&
            alloc.block->ptr + alloc.bsize >= alloc.block->allocs[alloc.index].ptr + size)
        {
            alloc.block->allocs[alloc.index].len = size;
            malloc_unlock_mutex();
            return ptr;
        }
        // Case 2 : The alloc is the last but the block isn't full
        else if (alloc.index < ALLOCS_COUNT - 1 && alloc.block->allocs[alloc.index + 1].ptr == NULL &&
            alloc.block->ptr + alloc.bsize >= alloc.block->allocs[alloc.index].ptr + size)
        {
            alloc.block->allocs[alloc.index].len = size;
            malloc_unlock_mutex();
            return ptr;
        }
        // Case 3 : The alloc is followed by an other
        else if (alloc.index < ALLOCS_COUNT - 1 && alloc.block->allocs[alloc.index + 1].ptr != NULL &&
            alloc.block->allocs[alloc.index + 1].ptr > alloc.block->allocs[alloc.index].ptr + size)
        {
            alloc.block->allocs[alloc.index].len = size;
            malloc_unlock_mutex();
            return ptr;
        }
        // Case 4 : Cannot be expanded, and need a new allocation
        else
        {
            size_t  len     = alloc.block->allocs[alloc.index].len;
	        void	*newptr = malloc(size);

            if (!newptr)
                return NULL;
            
			if (len <= size)
                ft_memcpy(newptr, ptr, len);
            else
                ft_memcpy(newptr, ptr, size);
            
            free(ptr);
            malloc_unlock_mutex();
            return newptr;
        }
    }
    else
    {
        ptr = malloc(size);
        malloc_unlock_mutex();
        return ptr;
    }
}
