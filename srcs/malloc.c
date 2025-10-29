#include "malloc.h"
#include "allocations.h"
#include "multithreading.h"
#include "system.h"
#include "libft.h"

static void	*insert_alloc(t_allocs_zone *zone, void *ptr, size_t size, size_t index)
{
	if (zone->allocs[index].ptr)
	{
		// Keeping ordered
		ft_memmove(
			&(zone->allocs[index + 1]),
			&(zone->allocs[index]),
			(ALLOCS_COUNT - index - 1) * sizeof(t_alloc)
		);
	}

	zone->allocs[index].ptr = ptr;
	zone->allocs[index].len = size;

	return ptr;
}

static void	*get_available_in_zone(t_allocs_zone *zone, size_t bsize, size_t size)
{
	// case 0 : all allocations of the zone are taken
	if (zone->allocs[ALLOCS_COUNT - 1].ptr)
		return NULL;

	for (size_t i = 0; i < ALLOCS_COUNT; ++i)
	{
		// The allocation is used
		if (zone->allocs[i].ptr)
		{
			// case 1 : there are space between our first allocation and the zone's begin
			if (i == 0)
			{
				if (zone->allocs[i].ptr - zone->ptr >= (ssize_t)size)
					return insert_alloc(zone, zone->ptr, size, i);
			}
			// case 2 : there are space between two allocations
			else
			{
				if (zone->allocs[i].ptr - zone->allocs[i - 1].ptr - zone->allocs[i - 1].len >= size)
					return insert_alloc(zone, zone->allocs[i - 1].ptr + zone->allocs[i -1].len, size, i);
			}
		}
		// case 3 : the zone is empty
		else if (i == 0)
		{
			return insert_alloc(zone, zone->ptr, size, 0);
		}
		// case 4 : there are space between the last allocation and the zone's end
		else if (zone->ptr + (ssize_t)bsize - zone->allocs[i - 1].ptr - zone->allocs[i - 1].len >= size)
		{
			return insert_alloc(zone, zone->allocs[i - 1].ptr + zone->allocs[i - 1].len, size, i);
		}
		// case 5 : there are not space
		else
			break ;
	}

	return NULL;
}

static void	*get_available(t_allocs_zone *zones, size_t count, size_t bsize, size_t size)
{
	void	*ptr	= NULL;

	for (size_t i = 0; i < count; ++i)
	{
		if (zones[i].ptr)
		{
			if ((ptr = get_available_in_zone(&(zones[i]), bsize, size)))
				return ptr;
		}
		else
			break ;
	}

	return NULL;
}

static void	*get_new_zone_alloc(t_allocs_zone *zones, size_t count, size_t bsize, size_t size)
{
	for (size_t i = 0; i < count; ++i)
	{
		if (!zones[i].ptr)
		{
			zones[i].ptr = mmap(NULL, bsize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
			if (!zones[i].ptr)
				return NULL;
			zones[i].allocs[0].ptr = zones[i].ptr;
			zones[i].allocs[0].len = size;
			return zones[i].ptr;
		}
	}

	return NULL;
}

static void	*get_alloc(t_allocs_zone *zones, size_t count, size_t bsize, size_t size)
{
	void	*ptr	= NULL;

	malloc_lock_mutex();
	if (bsize && (ptr = get_available(zones, count, bsize, size)))
	{
		malloc_unlock_mutex();
		return ptr;
	}
	else if ((ptr = get_new_zone_alloc(zones, count, bsize > 0 ? bsize : size, size)))
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
		return get_alloc(zones_g.tiny_zones, TINY_ZONES_COUNT, TINY_ZONE_SIZE, size);
	else if (size <= SMALL_ALLOC_SIZE)
		return get_alloc(zones_g.small_zones, SMALL_ZONES_COUNT, SMALL_ZONE_SIZE, size);
	else if (size <= get_malloc_limit())
		return get_alloc(zones_g.big_zones, BIG_ZONES_COUNT, 0, size);
	else
		return NULL;	
}

