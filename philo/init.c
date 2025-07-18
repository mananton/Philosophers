#include "philo.h"

int	init_mutexes(t_rules *rules)
{
	int	i;

	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->n_philo);
	if (!rules->forks)
		return (1);
	i = 0;
	while (i < rules->n_philo)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&rules->print_mutex, NULL))
		return (1);
	return (0);
}

int	init_philos(t_philo **philos, t_rules *rules)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * rules->n_philo);
	if (!*philos)
		return (1);
	i = 0;
	while (i < rules->n_philo)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].left_fork = i;
		(*philos)[i].right_fork = (i + 1) % rules->n_philo;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].last_meal = 0;
		(*philos)[i].rules = rules;
		i++;
	}
	return (0);
}

