#include "libft_malloc.h"
#include "multithreading.h"

static pthread_once_t once_control = PTHREAD_ONCE_INIT;
pthread_mutex_t malloc_mutex_g = PTHREAD_MUTEX_INITIALIZER;
pthread_mutexattr_t malloc_mutex_attr_g;

void initialize_mutex()
{
    pthread_mutexattr_init(&malloc_mutex_attr_g);
    pthread_mutexattr_settype(&malloc_mutex_attr_g, PTHREAD_MUTEX_RECURSIVE_NP);
    pthread_mutex_init(&malloc_mutex_g, &malloc_mutex_attr_g);
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