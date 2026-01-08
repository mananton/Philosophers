/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 12:45:00 by mananton          #+#    #+#             */
/*   Updated: 2026/01/08 12:24:42 by mananton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, const char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philo->rules->print_mutex);
	if (!philo->rules->stop)
	{
		timestamp = get_time() - philo->rules->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->rules->print_mutex);
}

static void	eat_with_forks(t_philo *philo, pthread_mutex_t *first_fork,
			pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(&philo->rules->meal_check);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->rules->meal_check);
	print_state(philo, "is eating");
	msleep_until_stop(philo->rules, philo->rules->time_eat);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

static int	is_stopped(t_rules *rules)
{
	int	stop;

	pthread_mutex_lock(&rules->print_mutex);
	stop = rules->stop;
	pthread_mutex_unlock(&rules->print_mutex);
	return (stop);
}

static void	eat_attempt_loop(t_philo *philo, pthread_mutex_t *first_fork,
			pthread_mutex_t *second_fork)
{
	while (!is_stopped(philo->rules))
	{
		pthread_mutex_lock(first_fork);
		print_state(philo, "has taken a fork");
		if (is_stopped(philo->rules))
		{
			pthread_mutex_unlock(first_fork);
			return ;
		}
		pthread_mutex_lock(second_fork);
		print_state(philo, "has taken a fork");
		if (is_stopped(philo->rules))
		{
			pthread_mutex_unlock(second_fork);
			pthread_mutex_unlock(first_fork);
			return ;
		}
		eat_with_forks(philo, first_fork, second_fork);
		return ;
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	first_fork = philo->left_fork;
	second_fork = philo->right_fork;
	if (first_fork > second_fork)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	eat_attempt_loop(philo, first_fork, second_fork);
}
