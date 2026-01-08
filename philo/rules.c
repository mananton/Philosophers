/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:41:02 by mananton          #+#    #+#             */
/*   Updated: 2026/01/06 11:17:00 by mananton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	alloc_structs(t_rules *r)
{
	r->forks = malloc(sizeof(pthread_mutex_t) * r->num_philo);
	r->philos = malloc(sizeof(t_philo) * r->num_philo);
	if (!r->forks || !r->philos)
		return (1);
	return (0);
}

static int	init_forks(t_rules *r)
{
	int	i;

	i = 0;
	while (i < r->num_philo)
	{
		if (pthread_mutex_init(&r->forks[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

int	init_rules(t_rules *r, int argc, char **argv)
{
	memset(r, 0, sizeof(t_rules));
	if (argc != 5 && argc != 6)
		return (1);
	r->num_philo = ft_atoi(argv[1]);
	r->time_die = ft_atoi(argv[2]);
	r->time_eat = ft_atoi(argv[3]);
	r->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		r->must_eat = ft_atoi(argv[5]);
	else
		r->must_eat = -1;
	if (r->num_philo <= 0 || r->time_die <= 0 || r->time_eat <= 0
		|| r->time_sleep <= 0 || (argc == 6 && r->must_eat <= 0))
		return (1);
	if (alloc_structs(r) || init_forks(r))
		return (1);
	if (pthread_mutex_init(&r->print_mutex, NULL)
		|| pthread_mutex_init(&r->meal_check, NULL))
		return (1);
	return (0);
}

int	init_philosophers(t_rules *rules)
{
	int		i;
	t_philo	*ph;

	i = 0;
	while (i < rules->num_philo)
	{
		ph = &rules->philos[i];
		ph->id = i + 1;
		ph->meals_eaten = 0;
		ph->last_meal = 0;
		ph->left_fork = &rules->forks[i];
		ph->right_fork = &rules->forks[(i + 1) % rules->num_philo];
		ph->rules = rules;
		i++;
	}
	return (0);
}

void	destroy_mutexes(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->num_philo)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&rules->print_mutex);
	pthread_mutex_destroy(&rules->meal_check);
}
