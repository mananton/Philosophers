/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:40:40 by mananton          #+#    #+#             */
/*   Updated: 2025/09/02 11:40:41 by mananton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_philo(t_rules *rules, int i)
{
	pthread_mutex_lock(&rules->meal_check);
	if (get_time() - rules->philos[i].last_meal > rules->time_die)
	{
		pthread_mutex_lock(&rules->print_mutex);
		printf("%ld %d died\n", get_time() - rules->start_time,
			rules->philos[i].id);
		rules->stop = 1;
		pthread_mutex_unlock(&rules->print_mutex);
	}
	else if (rules->must_eat != -1
		&& rules->finished_eating >= rules->num_philo)
		rules->stop = 1;
	pthread_mutex_unlock(&rules->meal_check);
}

void	*monitor_routine(void *arg)
{
	t_rules	*rules;
	int		i;

	rules = (t_rules *)arg;
	while (!rules->stop)
	{
		i = 0;
		while (i < rules->num_philo && !rules->stop)
		{
			check_philo(rules, i);
			usleep(1000);
			i++;
		}
	}
	return (NULL);
}
