#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

typedef struct s_rules t_rules;

typedef struct s_philo {
    int     id;
    int     meals_eaten;
    long    last_meal;
    pid_t   pid;
    t_rules *rules;
}   t_philo;

struct s_rules {
    int     num_philo;
    long    time_die;
    long    time_eat;
    long    time_sleep;
    int     must_eat;
    long    start_time;
    int     finished_eating;
    int     stop;
    sem_t   *forks;
    sem_t   *print_sem;
    sem_t   *meal_sem;
    t_philo *philos;
};

long    get_time(void);
void    msleep(long ms);
int     ft_atoi(const char *str);
int     init_rules(t_rules *rules, int argc, char **argv);
int     init_philosophers(t_rules *rules);
void    cleanup(t_rules *rules);
void    *death_monitor(void *arg);
void    philosopher_life(t_philo *philo);
int     wait_children(t_rules *rules);

#endif
