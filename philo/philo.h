#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_rules
{
	int	n_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int	must_eat;
	int	someone_died;
	long	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
}	t_rules;

typedef struct s_philo
{
	int	id;
	int	left_fork;
	int	right_fork;
	long	last_meal;
	int	meals_eaten;
	pthread_t	thread_id;
	t_rules	*rules;
}	t_philo;

int	parse_args(int argc, char **argv, t_rules *rules);
int	init_mutexes(t_rules *rules);
int	init_philos(t_philo **philos, t_rules *rules);
void *routine(void *arg);
void take_forks(t_philo *philo);
void eat(t_philo *philo);
void drop_forks(t_philo *philo);
long	get_time_ms(void);
void	*monitor(void *arg);
void print_state(t_philo *philo, char *msg);

#endif
