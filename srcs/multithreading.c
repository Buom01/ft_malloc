#include "malloc.h"
#include "multithreading.h"

static pthread_once_t once_control = PTHREAD_ONCE_INIT;
pthread_mutex_t malloc_mutex_g = PTHREAD_MUTEX_INITIALIZER;

void initialize_mutex()
{
    pthread_mutex_init(&malloc_mutex_g, NULL);
}

void malloc_lock_mutex()
{
    pthread_once(&once_control, initialize_mutex);
    pthread_mutex_lock(&malloc_mutex_g);
}

void malloc_unlock_mutex()
{
    pthread_mutex_unlock(&malloc_mutex_g);
}