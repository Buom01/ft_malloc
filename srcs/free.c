#include "malloc.h"
#include "allocations.h"
#include "multithreading.h"
#include "libft.h"

static bool free_in_zone(t_allocs_zone *zone, void *ptr)
{
	for (ssize_t i = ALLOCS_COUNT - 1; i >= 0; --i)
	{
		if (zone->allocs[i].ptr == ptr)
		{
			// Defragement
			ft_memmove(
				&(zone->allocs[i]),
				&(zone->allocs[i + 1]),
				(ALLOCS_COUNT - i - 1) * sizeof(t_alloc)
			);
			ft_bzero(&(zone->allocs[ALLOCS_COUNT - 1]), sizeof(t_alloc));

			return true;
		}
	}
	return false;
}

static bool	free_in_zones(t_allocs_zone *zones, size_t count, size_t bsize, void *ptr)
{
	for (ssize_t i = count - 1; i >= 0; --i)
	{
		if (zones[i].ptr && zones[i].ptr <= ptr && zones[i].ptr + bsize >= ptr)
			return free_in_zone(&(zones[i]), ptr);
	}
	return false;
}

static void	freeup_zones(t_allocs_zone *zones, size_t count, size_t bsize)
{
	// Don't even keep a mmap zone if no malloc
	for (size_t i = 0; i < count; ++i)
	{
		if (zones[i].ptr && !zones[i].allocs[0].ptr)
		{
			munmap(zones[i].ptr, bsize);
			zones[i].ptr = 0;
		}
	}
}

void free(void *ptr)
{
	if (!ptr)
		return ;

	malloc_lock_mutex();
	if (free_in_zones(zones_g.tiny_zones, TINY_ZONES_COUNT, TINY_ZONE_SIZE, ptr))
		freeup_zones(zones_g.tiny_zones, TINY_ZONES_COUNT, TINY_ZONE_SIZE);
	else if (free_in_zones(zones_g.small_zones, SMALL_ZONES_COUNT, SMALL_ZONE_SIZE, ptr))
		freeup_zones(zones_g.tiny_zones, SMALL_ZONES_COUNT, SMALL_ZONE_SIZE);
	else if (free_in_zones(zones_g.big_zones, BIG_ZONES_COUNT, 0, ptr))
		freeup_zones(zones_g.tiny_zones, BIG_ZONES_COUNT, 0);
	else
	{
		// Double free
	}
	malloc_unlock_mutex();
}
