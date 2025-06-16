#include "philo.h"

int init_rules(t_rules *rules, int argc, char **argv)
{
    int i;

    memset(rules, 0, sizeof(t_rules));
    if (argc != 5 && argc != 6)
        return (1);
    rules->num_philo = ft_atoi(argv[1]);
    rules->time_die = ft_atoi(argv[2]);
    rules->time_eat = ft_atoi(argv[3]);
    rules->time_sleep = ft_atoi(argv[4]);
    rules->must_eat = (argc == 6) ? ft_atoi(argv[5]) : -1;
    if (rules->num_philo <= 0 || rules->time_die <= 0 ||
        rules->time_eat <= 0 || rules->time_sleep <= 0 ||
        (argc == 6 && rules->must_eat <= 0))
        return (1);
    rules->forks = malloc(sizeof(pthread_mutex_t) * rules->num_philo);
    rules->philos = malloc(sizeof(t_philo) * rules->num_philo);
    if (!rules->forks || !rules->philos)
        return (1);
    i = 0;
    while (i < rules->num_philo)
    {
        if (pthread_mutex_init(&rules->forks[i], NULL))
            return (1);
        i++;
    }
    if (pthread_mutex_init(&rules->print_mutex, NULL) ||
        pthread_mutex_init(&rules->meal_check, NULL))
        return (1);
    return (0);
}

int init_philosophers(t_rules *rules)
{
    int i;
    t_philo *ph;

    i = 0;
    while (i < rules->num_philo)
    {
        ph = &rules->philos[i];
        ph->id = i + 1;
        ph->meals_eaten = 0;
        ph->last_meal = rules->start_time;
        ph->left_fork = &rules->forks[i];
        ph->right_fork = &rules->forks[(i + 1) % rules->num_philo];
        ph->rules = rules;
        i++;
    }
    return (0);
}

void destroy_mutexes(t_rules *rules)
{
    int i = 0;

    while (i < rules->num_philo)
    {
        pthread_mutex_destroy(&rules->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&rules->print_mutex);
    pthread_mutex_destroy(&rules->meal_check);
}
