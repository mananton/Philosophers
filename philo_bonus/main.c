#include "philo_bonus.h"

static void spawn_philos(t_rules *rules)
{
    int i = 0;

    while (i < rules->num_philo)
    {
        rules->philos[i].pid = fork();
        if (rules->philos[i].pid == 0)
        {
            philosopher_life(&rules->philos[i]);
            exit(0);
        }
        i++;
    }
}

int main(int argc, char **argv)
{
    t_rules rules;

    if (init_rules(&rules, argc, argv))
    {
        printf("Error: invalid arguments\n");
        return (1);
    }
    rules.start_time = get_time();
    if (init_philosophers(&rules))
        return (1);
    spawn_philos(&rules);
    wait_children(&rules);
    cleanup(&rules);
    return (0);
}
