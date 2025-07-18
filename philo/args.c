#include "philo.h"

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_atoi(const char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i] && is_digit(str[i]))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

int	parse_args(int argc, char **argv, t_rules *rules)
{
	if (argc != 5 && argc != 6)
		return (1);
	rules->n_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules->must_eat = ft_atoi(argv[5]);
	else
		rules->must_eat = -1;
	return (0);
}
