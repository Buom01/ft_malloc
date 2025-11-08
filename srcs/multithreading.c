#include "malloc.h"
#include "multithreading.h"

pthread_mutex_t malloc_mutex_g = PTHREAD_MUTEX_INITIALIZER;

void malloc_lock_mutex()
{
    pthread_mutex_lock(&malloc_mutex_g);
}

void malloc_unlock_mutex()
{
    pthread_mutex_unlock(&malloc_mutex_g);
}