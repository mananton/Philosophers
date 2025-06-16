#include "philo_bonus.h"

static void print_state(t_philo *philo, const char *msg)
{
    long timestamp;

    sem_wait(philo->rules->print_sem);
    if (!philo->rules->stop)
    {
        timestamp = get_time() - philo->rules->start_time;
        printf("%ld %d %s\n", timestamp, philo->id, msg);
    }
    sem_post(philo->rules->print_sem);
}

static int  check_stop(t_philo *philo, int after_meal)
{
    if (after_meal && philo->rules->must_eat != -1 &&
        philo->meals_eaten >= philo->rules->must_eat)
    {
        sem_wait(philo->rules->meal_sem);
        philo->rules->finished_eating++;
        sem_post(philo->rules->meal_sem);
    }
    if (philo->rules->must_eat != -1 &&
        philo->rules->finished_eating >= philo->rules->num_philo)
        philo->rules->stop = 1;
    if (get_time() - philo->last_meal > philo->rules->time_die)
    {
        sem_wait(philo->rules->print_sem);
        printf("%ld %d died\n", get_time() - philo->rules->start_time,
            philo->id);
        philo->rules->stop = 1;
        sem_post(philo->rules->print_sem);
        sem_post(philo->rules->meal_sem);
        exit(1);
    }
    return (philo->rules->stop);
}

static int  eat_cycle(t_philo *philo)
{
    sem_wait(philo->rules->forks);
    print_state(philo, "has taken a fork");
    sem_wait(philo->rules->forks);
    print_state(philo, "has taken a fork");
    sem_wait(philo->rules->meal_sem);
    print_state(philo, "is eating");
    philo->last_meal = get_time();
    philo->meals_eaten++;
    sem_post(philo->rules->meal_sem);
    msleep(philo->rules->time_eat);
    sem_post(philo->rules->forks);
    sem_post(philo->rules->forks);
    if (check_stop(philo, 1))
        return (1);
    print_state(philo, "is sleeping");
    msleep(philo->rules->time_sleep);
    print_state(philo, "is thinking");
    return (0);
}

void    philosopher_life(t_philo *philo)
{
    pthread_t monitor;

    philo->last_meal = get_time();
    pthread_create(&monitor, NULL, death_monitor, philo);
    if (philo->id % 2 == 0)
        usleep(1000);
    while (!philo->rules->stop)
    {
        if (eat_cycle(philo))
            break;
    }
    pthread_join(monitor, NULL);
    exit(0);
}


void    *death_monitor(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (!philo->rules->stop)
    {
        sem_wait(philo->rules->meal_sem);
        if (check_stop(philo, 0))
            return (NULL);
        sem_post(philo->rules->meal_sem);
        usleep(1000);
    }
    return (NULL);
}
