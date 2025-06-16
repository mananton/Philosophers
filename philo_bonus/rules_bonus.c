#include "philo_bonus.h"

static int  open_sems(t_rules *rules)
{
    sem_unlink("/forks_sem");
    sem_unlink("/print_sem");
    sem_unlink("/meal_sem");
    rules->forks = sem_open("/forks_sem", O_CREAT, 0644, rules->num_philo);
    rules->print_sem = sem_open("/print_sem", O_CREAT, 0644, 1);
    rules->meal_sem = sem_open("/meal_sem", O_CREAT, 0644, 1);
    if (rules->forks == SEM_FAILED || rules->print_sem == SEM_FAILED ||
        rules->meal_sem == SEM_FAILED)
        return (1);
    return (0);
}

int init_rules(t_rules *rules, int argc, char **argv)
{
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
    rules->philos = malloc(sizeof(t_philo) * rules->num_philo);
    if (!rules->philos)
        return (1);
    if (open_sems(rules))
        return (1);
    return (0);
}

int init_philosophers(t_rules *rules)
{
    int     i;
    t_philo *ph;

    i = 0;
    while (i < rules->num_philo)
    {
        ph = &rules->philos[i];
        ph->id = i + 1;
        ph->meals_eaten = 0;
        ph->last_meal = rules->start_time;
        ph->rules = rules;
        i++;
    }
    return (0);
}

void cleanup(t_rules *rules)
{
    sem_close(rules->forks);
    sem_close(rules->print_sem);
    sem_close(rules->meal_sem);
    sem_unlink("/forks_sem");
    sem_unlink("/print_sem");
    sem_unlink("/meal_sem");
    free(rules->philos);
}
