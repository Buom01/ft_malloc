#include "allocations.h"
#include "libft.h"

#define HEX_BASE "0123456789ABCDEF"

t_allocs_blocks	*get_blocks()
{
	static t_allocs_blocks	blocks;

	return &blocks;
}

static void show_alloc_dump(void *begin, void *end)
{
	for (void *i = begin; i < end; i += 16)
	{
		ft_putstr_fd("    ", STDOUT_FILENO);
		ft_putptr_fd_noalloc(i, STDOUT_FILENO);
		ft_putstr_fd(": ", STDOUT_FILENO);
		for (void *byte = i; byte < end && byte < i + 16; ++byte)
		{
			ft_putchar_fd(
				HEX_BASE[(*(unsigned char*)byte) / 16],
				STDOUT_FILENO
			);
			ft_putchar_fd(
				HEX_BASE[(*(unsigned char*)byte) % 16],
				STDOUT_FILENO
			);
			ft_putstr_fd(" ", STDOUT_FILENO);
		}
		ft_putstr_fd("| ", STDOUT_FILENO);
		for (void *byte = i; byte < end && byte < i + 16; ++byte)
			ft_putchar_fd( ft_isprint(*(char*)byte) ? *(char*)byte : '.', STDOUT_FILENO);
		ft_putendl_fd("", STDOUT_FILENO);
	}
}

static void show_allocs(t_alloc *allocs, size_t *total, size_t count, bool ext)
{
	for (size_t i = 0; i < count; ++i)
	{
		if (allocs[i].ptr)
		{
			if (ext)
				ft_putstr_fd("  - ", STDOUT_FILENO);
			ft_putptr_fd_noalloc(allocs[i].ptr, STDOUT_FILENO);
			ft_putstr_fd(" - ", STDOUT_FILENO);
			ft_putptr_fd_noalloc(allocs[i].ptr + allocs[i].len, STDOUT_FILENO);
			ft_putstr_fd(" : ", STDOUT_FILENO);
			ft_putnbr_fd_noalloc((int)allocs[i].len, STDOUT_FILENO);
			ft_putendl_fd(" bytes", STDOUT_FILENO);
			if (ext)
				show_alloc_dump(allocs[i].ptr, allocs[i].ptr + allocs[i].len);
			*total += allocs[i].len;
		}
	}
}

static void show_alloc_blocks(t_allocs_block *blocks, size_t count, char *name, size_t *total, bool ext)
{
	for (size_t i = 0; i < count; ++i)
	{
		if (blocks[i].ptr)
		{
			ft_putstr_fd(name, STDOUT_FILENO);
			ft_putstr_fd(" : ", STDOUT_FILENO);
			ft_putptr_fd_noalloc(blocks[i].ptr, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			show_allocs(blocks[i].allocs, total, ALLOCS_COUNT, ext);
		}
	}
}

static void show_alloc_mem_all(bool ext)
{
	size_t			total	= 0;
	t_allocs_blocks	*blocks = get_blocks();

	show_alloc_blocks(blocks->tiny_blocks, TINY_BLOCKS_COUNT, "TINY", &total, ext);
	show_alloc_blocks(blocks->small_blocks, SMALL_BLOCKS_COUNT, "SMALL", &total, ext);
	show_alloc_blocks(blocks->big_blocks, BIG_BLOCKS_COUNT, "BIG", &total, ext);
	
	ft_putstr_fd("Total : ", STDOUT_FILENO);
	ft_putnbr_fd_noalloc(total, STDOUT_FILENO);
	ft_putendl_fd(" bytes", STDOUT_FILENO);
}

void show_alloc_mem()
{
	show_alloc_mem_all(false);
}

void show_alloc_mem_ex()
{
	show_alloc_mem_all(true);
}
