#include "philo.h"

int ft_atoi(const char *str)
{
    long    res = 0;
    int     sign = 1;

    while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
        str++;
    if (*str == '+' || *str == '-')
        if (*str++ == '-')
            sign = -1;
    if (!*str)
        return (-1);
    while (*str >= '0' && *str <= '9')
    {
        res = res * 10 + (*str - '0');
        if (res * sign > INT_MAX || res * sign < INT_MIN)
            return (-1);
        str++;
    }
    if (*str)
        return (-1);
    return ((int)(res * sign));
}
