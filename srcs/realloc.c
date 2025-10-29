#include "malloc.h"
#include "allocations.h"
#include "multithreading.h"
#include "system.h"
#include "libft.h"

typedef struct s_alloc_info
{
    t_allocs_zone  *zone;
    size_t          index;
    size_t          bsize;
} t_alloc_info;

static void find_alloc_in_zone(t_allocs_zone *zone, size_t bsize, void *ptr, t_alloc_info *alloc)
{
	for (ssize_t i = ALLOCS_COUNT - 1; i >= 0; --i)
	{
		if (zone->allocs[i].ptr == ptr)
		{
            alloc->zone = zone;
            alloc->bsize = bsize;
            alloc->index = i;
            break ;
		}
	}
}

static void	find_alloc_in_zones(t_allocs_zone *zones, size_t count, size_t bsize, void *ptr, t_alloc_info *alloc)
{
	for (ssize_t i = count - 1; i >= 0; --i)
	{
		if (zones[i].ptr && zones[i].ptr <= ptr && zones[i].ptr + bsize >= ptr)
        {
			find_alloc_in_zone(&(zones[i]), bsize, ptr, alloc);
            break;
        }
	}
}

static void find_alloc(void *ptr, t_alloc_info *alloc)
{

	if (!ptr)
		return;

    find_alloc_in_zones(zones_g.tiny_zones, TINY_ZONES_COUNT, TINY_ZONE_SIZE, ptr, alloc);
    if (alloc->zone)
        return ;
    find_alloc_in_zones(zones_g.small_zones, SMALL_ZONES_COUNT, SMALL_ZONE_SIZE, ptr, alloc);
    if (alloc->zone)
        return ;
    find_alloc_in_zones(zones_g.big_zones, BIG_ZONES_COUNT, 0, ptr, alloc);
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

    if (alloc.zone)
    {
        // Case 0 : The new allocation is smaller (or equal)
        if (alloc.zone->allocs[alloc.index].len >= size)
        {
            alloc.zone->allocs[alloc.index].len = size;
            malloc_unlock_mutex();
            return ptr;
        }
        // Case 1 : The zone is full and the alloc is the last
        else if (alloc.index == ALLOCS_COUNT - 1 &&
            alloc.zone->ptr + alloc.bsize >= alloc.zone->allocs[alloc.index].ptr + size)
        {
            alloc.zone->allocs[alloc.index].len = size;
            malloc_unlock_mutex();
            return ptr;
        }
        // Case 2 : The alloc is the last but the zone isn't full
        else if (alloc.index < ALLOCS_COUNT - 1 && alloc.zone->allocs[alloc.index + 1].ptr == NULL &&
            alloc.zone->ptr + alloc.bsize >= alloc.zone->allocs[alloc.index].ptr + size)
        {
            alloc.zone->allocs[alloc.index].len = size;
            malloc_unlock_mutex();
            return ptr;
        }
        // Case 3 : The alloc is followed by an other
        else if (alloc.index < ALLOCS_COUNT - 1 && alloc.zone->allocs[alloc.index + 1].ptr != NULL &&
            alloc.zone->allocs[alloc.index + 1].ptr > alloc.zone->allocs[alloc.index].ptr + size)
        {
            alloc.zone->allocs[alloc.index].len = size;
            malloc_unlock_mutex();
            return ptr;
        }
        // Case 4 : Cannot be expanded, and need a new allocation
        else
        {
            size_t  len     = alloc.zone->allocs[alloc.index].len;
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
