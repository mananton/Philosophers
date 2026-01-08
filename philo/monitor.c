/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:40:40 by mananton          #+#    #+#             */
/*   Updated: 2026/01/06 12:25:28 by mananton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_start(t_rules *rules)
{
	while (1)
	{
		pthread_mutex_lock(&rules->meal_check);
		if (rules->start_time != 0)
		{
			pthread_mutex_unlock(&rules->meal_check);
			break ;
		}
		pthread_mutex_unlock(&rules->meal_check);
		usleep(200);
	}
}

static int	is_stopped(t_rules *rules)
{
	int	stop;

	pthread_mutex_lock(&rules->print_mutex);
	stop = rules->stop;
	pthread_mutex_unlock(&rules->print_mutex);
	return (stop);
}

static void	report_death(t_rules *rules, long now, int philo_id)
{
	pthread_mutex_lock(&rules->print_mutex);
	if (philo_id == 0)
		rules->stop = 1;
	else if (!rules->stop)
	{
		printf("%ld %d died\n", now - rules->start_time, philo_id);
		rules->stop = 1;
	}
	pthread_mutex_unlock(&rules->print_mutex);
}

static void	check_philo(t_rules *rules, int i)
{
	long	now;
	long	last_meal;
	int		all_finished;
	int		philo_id;

	now = get_time();
	all_finished = 0;
	pthread_mutex_lock(&rules->meal_check);
	last_meal = rules->philos[i].last_meal;
	philo_id = rules->philos[i].id;
	if (rules->must_eat != -1 && rules->finished_eating >= rules->num_philo)
		all_finished = 1;
	pthread_mutex_unlock(&rules->meal_check);
	if (all_finished)
		report_death(rules, now, 0);
	else if (now - last_meal >= rules->time_die)
		report_death(rules, now, philo_id);
}

void	*monitor_routine(void *arg)
{
	t_rules	*rules;
	int		i;

	rules = (t_rules *)arg;
	wait_start(rules);
	while (!is_stopped(rules))
	{
		i = 0;
		while (i < rules->num_philo && !is_stopped(rules))
		{
			check_philo(rules, i);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
