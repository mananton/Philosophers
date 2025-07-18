#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->rules->forks[philo->right_fork]);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(&philo->rules->forks[philo->left_fork]);
		print_state(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->rules->forks[philo->left_fork]);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(&philo->rules->forks[philo->right_fork]);
		print_state(philo, "has taken a fork");
	}
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->rules->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->rules->forks[philo->right_fork]);
}

void	eat(t_philo *philo)
{
	philo->last_meal = get_time_ms();
	print_state(philo, "is eating");
	usleep(philo->rules->time_to_eat * 1000);
	philo->meals_eaten++;
}

void	go_sleep(t_philo *philo)
{
	print_state(philo, "is sleeping");
	usleep(philo->rules->time_to_sleep * 1000);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (!philo->rules->someone_died)
	{
		print_state(philo, "is thinking");
		take_forks(philo);
		if (philo->rules->someone_died)
		{
			drop_forks(philo);
			break;
		}
		eat(philo);
		drop_forks(philo);
		go_sleep(philo);
	}
	return (NULL);
}
