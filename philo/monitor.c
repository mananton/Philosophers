#include "philo.h"

void	*monitor(void *arg)
{
	t_philo	*philos;
	t_rules	*rules;
	int		i;
	long	now;

	philos = (t_philo *)arg;
	rules = philos[0].rules;
	while (!rules->someone_died)
	{
		i = 0;
		while (i < rules->n_philo)
		{
			now = get_time_ms();
			if (now - philos[i].last_meal > rules->time_to_die)
			{
				pthread_mutex_lock(&rules->print_mutex);
				printf("%ld %d died\n", now - rules->start_time, philos[i].id);
				pthread_mutex_unlock(&rules->print_mutex);
				rules->someone_died = 1;
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
