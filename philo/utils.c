/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:41:06 by mananton          #+#    #+#             */
/*   Updated: 2026/01/08 12:49:26 by mananton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	msleep(long ms)
{
	long	end;
	long	now;
	long	remaining;

	end = get_time() + ms;
	while (1)
	{
		now = get_time();
		if (now >= end)
			break ;
		remaining = end - now;
		if (remaining > 2)
			usleep((remaining - 1) * 1000);
		else
			usleep(200);
	}
}

void	msleep_until_stop(t_rules *rules, long ms)
{
	long	end;
	long	now;
	long	remaining;
	int		stop;

	end = get_time() + ms;
	while (1)
	{
		pthread_mutex_lock(&rules->print_mutex);
		stop = rules->stop;
		pthread_mutex_unlock(&rules->print_mutex);
		if (stop)
			break ;
		now = get_time();
		if (now >= end)
			break ;
		remaining = end - now;
		if (remaining > 10)
			usleep(1000);
		else
			usleep(200);
	}
}

static long	get_time_us(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000L + tv.tv_usec);
}

void	usleep_until_stop(t_rules *rules, long us)
{
	long	end;
	long	now;
	long	remaining;
	long	chunk;
	int		stop;

	end = get_time_us() + us;
	while (1)
	{
		pthread_mutex_lock(&rules->print_mutex);
		stop = rules->stop;
		pthread_mutex_unlock(&rules->print_mutex);
		if (stop)
			break ;
		now = get_time_us();
		if (now >= end)
			break ;
		remaining = end - now;
		chunk = remaining;
		if (chunk > 1000)
			chunk = 1000;
		usleep(chunk);
	}
}
