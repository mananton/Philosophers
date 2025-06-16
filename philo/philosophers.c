#include "philo.h"

static void print_state(t_philo *philo, const char *msg)
{
    long timestamp;

    pthread_mutex_lock(&philo->rules->print_mutex);
    if (!philo->rules->stop)
    {
        timestamp = get_time() - philo->rules->start_time;
        printf("%ld %d %s\n", timestamp, philo->id, msg);
    }
    pthread_mutex_unlock(&philo->rules->print_mutex);
}

static void eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_state(philo, "has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    print_state(philo, "has taken a fork");
    pthread_mutex_lock(&philo->rules->meal_check);
    print_state(philo, "is eating");
    philo->last_meal = get_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->rules->meal_check);
    msleep(philo->rules->time_eat);
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

void    *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->id % 2 == 0)
        usleep(1000);
    while (!philo->rules->stop)
    {
        eat(philo);
        if (philo->rules->must_eat != -1 &&
            philo->meals_eaten >= philo->rules->must_eat)
        {
            pthread_mutex_lock(&philo->rules->meal_check);
            philo->rules->finished_eating++;
            pthread_mutex_unlock(&philo->rules->meal_check);
            break;
        }
        print_state(philo, "is sleeping");
        msleep(philo->rules->time_sleep);
        print_state(philo, "is thinking");
    }
    return (NULL);
}
