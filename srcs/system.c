#include "libft_malloc.h"
#include "multithreading.h"

rlim_t get_malloc_limit()
{
    static rlim_t limit = 0;

    if (limit != 0)
        return limit;

    malloc_lock_mutex();
    struct rlimit rl;
    if (getrlimit(RLIMIT_DATA, &rl) == 0)
        limit = rl.rlim_cur;
    else
        limit = ((rlim_t)1024*1024*1024*5);
    malloc_unlock_mutex();

    return limit;
}