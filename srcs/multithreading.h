#ifndef MULTITHREADING_H
# define MULTITHREADING_H

# include <pthread.h>

extern pthread_mutex_t malloc_mutex_g;

void malloc_lock_mutex();
void malloc_unlock_mutex();

#endif