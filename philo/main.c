#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules		rules;
	t_philo		*philos;
	pthread_t	monitor_thread;
	int			i;

	if (parse_args(argc, argv, &rules))
	{
		write(2, "Error: argumentos invalidos\n", 28);
		return (1);
	}
	if (init_mutexes(&rules))
	{
		write(2, "Erro ao inicializar mutexes\n", 28);
		return (1);
	}
	if (init_philos(&philos, &rules))
	{
		write(2, "Erro ao inicializar filosofos\n", 30);
		return (1);
	}
	rules.start_time = get_time_ms();
	i = 0;
	while (i < rules.n_philo)
	{
		philos[i].last_meal = rules.start_time;
		pthread_create(&philos[i].thread_id, NULL, &routine, &philos[i]);
		i++;
	}
	pthread_create(&monitor_thread, NULL, &monitor, philos);
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < rules.n_philo)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}
	return (0);
}
