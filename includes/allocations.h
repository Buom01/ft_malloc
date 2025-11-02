#ifndef ALLOCATIONS_H
# define ALLOCATIONS_H

# include "malloc.h"

# define ALLOCS_COUNT 128 // Number of allocation for a single zone
# define TINY_ALLOC_SIZE 128 // n — Allocation up to SIZE can go in that zone
# define SMALL_ALLOC_SIZE 2048 // m
# define TINY_ZONE_SIZE (sysconf(_SC_PAGESIZE)) * 10 // N — Representing a single zone size
# define SMALL_ZONE_SIZE (sysconf(_SC_PAGESIZE) * 500) // M
# define TINY_ZONES_COUNT 1024 // Multipling zone up to COUNT time
# define SMALL_ZONES_COUNT 1024
# define BIG_ZONES_COUNT 1024 * ALLOCS_COUNT

# define ALIGNEMENT 16  // Bytes
# define ALIGN(size) (((size) + (ALIGNEMENT - 1)) & ~(ALIGNEMENT - 1));  // Round up at ALIGNEMENT on the ceil — Popular formula

typedef struct s_alloc
{
	void	*ptr;
	size_t	len;	
} t_alloc;

typedef struct s_allocs_zone
{
	void		*ptr;
	t_alloc		allocs[ALLOCS_COUNT];
} t_allocs_zone;

typedef struct s_allocs_zones
{
	t_allocs_zone	tiny_zones[TINY_ZONES_COUNT];
	t_allocs_zone	small_zones[SMALL_ZONES_COUNT];
	t_allocs_zone	big_zones[BIG_ZONES_COUNT];
} t_allocs_zones;

extern t_allocs_zones	zones_g;

#endif
