#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

typedef struct s_rules t_rules;

typedef struct s_philo {
    int             id;
    int             meals_eaten;
    long            last_meal;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_rules         *rules;
}   t_philo;

struct s_rules {
    int             num_philo;
    long            time_die;
    long            time_eat;
    long            time_sleep;
    int             must_eat;
    long            start_time;
    int             finished_eating;
    int             stop;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    pthread_mutex_t meal_check;
    t_philo         *philos;
};

long    get_time(void);
void    msleep(long ms);
int     ft_atoi(const char *str);
int     init_rules(t_rules *rules, int argc, char **argv);
int     init_philosophers(t_rules *rules);
void    destroy_mutexes(t_rules *rules);

void    *philo_routine(void *arg);
void    *monitor_routine(void *arg);

#endif
