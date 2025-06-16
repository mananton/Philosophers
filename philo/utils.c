#include "philo.h"

long    get_time(void)
{
    struct timeval  tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void    msleep(long ms)
{
    long    start = get_time();
    while (get_time() - start < ms)
        usleep(100);
}


