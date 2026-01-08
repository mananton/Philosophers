/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:40:31 by mananton          #+#    #+#             */
/*   Updated: 2026/01/08 10:49:35 by mananton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	run_single_philo(t_rules *rules)
{
	t_philo	*p;

	p = &rules->philos[0];
	pthread_mutex_lock(&rules->meal_check);
	rules->start_time = get_time();
	p->last_meal = rules->start_time;
	pthread_mutex_unlock(&rules->meal_check);
	pthread_mutex_lock(&rules->forks[0]);
	pthread_mutex_lock(&rules->print_mutex);
	printf("%ld %d has taken a fork\n", get_time() - rules->start_time, p->id);
	pthread_mutex_unlock(&rules->print_mutex);
	msleep(rules->time_die);
	pthread_mutex_lock(&rules->print_mutex);
	printf("%ld %d died\n", get_time() - rules->start_time, p->id);
	pthread_mutex_unlock(&rules->print_mutex);
	pthread_mutex_unlock(&rules->forks[0]);
}

static void	start_simulation(t_rules *rules, pthread_t *monitor)
{
	int	i;

	i = 0;
	while (i < rules->num_philo)
	{
		pthread_create(&rules->philos[i].thread, NULL, philo_routine,
			&rules->philos[i]);
		i++;
	}
	pthread_mutex_lock(&rules->meal_check);
	rules->start_time = get_time();
	i = 0;
	while (i < rules->num_philo)
	{
		rules->philos[i].last_meal = rules->start_time;
		i++;
	}
	pthread_mutex_unlock(&rules->meal_check);
	pthread_create(monitor, NULL, monitor_routine, rules);
}

static void	join_threads(t_rules *rules, pthread_t monitor)
{
	int	i;

	i = 0;
	while (i < rules->num_philo)
	{
		pthread_join(rules->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}

static void	cleanup(t_rules *r)
{
	destroy_mutexes(r);
	free(r->forks);
	free(r->philos);
}

int	main(int argc, char **argv)
{
	t_rules		rules;
	pthread_t	monitor;

	if (init_rules(&rules, argc, argv))
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	rules.start_time = 0;
	if (init_philosophers(&rules))
		return (1);
	if (rules.num_philo == 1)
	{
		run_single_philo(&rules);
		cleanup(&rules);
		return (0);
	}
	start_simulation(&rules, &monitor);
	join_threads(&rules, monitor);
	cleanup(&rules);
	return (0);
}
