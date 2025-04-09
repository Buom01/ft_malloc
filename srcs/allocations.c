#include "allocations.h"

t_allocs_blocks	get_blocks()
{
	static t_allocs_blocks	blocks = {0};

	return blocks;
}

static void show_allocs(t_alloc *allocs, size_t *total, size_t count)
{
	for (size_t i = 0; i < count; ++i)
	{
		if (allocs[i].ptr)
		{
			ft_putptr_fd(allocs[i].ptr, STDOUT_FILENO);
			ft_putstr_fd(" - ", STDOUT_FILENO);
			ft_putptr_fd(allocs[i].ptr + allocs[i].len, STDOUT_FILENO);
			ft_putstr_fd(" : ", STDOUT_FILENO);
			ft_putnbr_fd(allocs[i].len, STDOUT_FILENO);
			ft_putendl_fd(" bytes", STDOUT_FILENO);
			*total += allocs[i].len;
		}
	}
}

static void show_alloc_blocks(t_allocs_block *blocks, size_t count, char *name, size_t *total)
{
	for (size_t i = 0; i < count; ++i)
	{
		if (blocks[i].ptr)
		{
			ft_putstr_fd(name, STDOUT_FILENO);
			ft_putstr_fd(" : ", STDOUT_FILENO);
			ft_putptr_fd(blocks[i].ptr, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			show_allocs(blocks[i].allocs, total, ALLOCS_COUNT);
		}
	}
}

void show_alloc_mem()
{
	size_t			total;
	t_allocs_blocks	blocks = get_blocks();

	show_alloc_blocks(blocks.tiny_blocks, TINY_BLOCKS_COUNT, "TINY", &total);
	show_alloc_blocks(blocks.small_blocks, SMALL_BLOCKS_COUNT, "SMALL", &total);
	
	ft_putstr_fd("Total : ", STDOUT_FILENO);
	ft_putnbr_fd(total, STDOUT_FILENO);
	ft_putendl_fd(" bytes", STDOUT_FILENO);
}
