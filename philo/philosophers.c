/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:40:57 by mananton          #+#    #+#             */
/*   Updated: 2026/01/08 12:35:08 by mananton         ###   ########.fr       */
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

static int	mark_done_if_needed(t_philo *philo)
{
	int	done;

	pthread_mutex_lock(&philo->rules->meal_check);
	done = (philo->rules->must_eat != -1
			&& philo->meals_eaten >= philo->rules->must_eat);
	if (done)
		philo->rules->finished_eating++;
	pthread_mutex_unlock(&philo->rules->meal_check);
	return (done);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_start(philo->rules);
	if (philo->id % 2 == 0)
		usleep_until_stop(philo->rules, (philo->rules->time_eat / 2) * 1000);
	while (!is_stopped(philo->rules))
	{
		eat(philo);
		if (mark_done_if_needed(philo))
			break ;
		print_state(philo, "is sleeping");
		msleep_until_stop(philo->rules, philo->rules->time_sleep);
		print_state(philo, "is thinking");
		if (philo->rules->num_philo % 2 != 0)
			usleep_until_stop(philo->rules, 200);
	}
	return (NULL);
}
