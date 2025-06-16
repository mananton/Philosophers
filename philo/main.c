#include "philo.h"

static void create_threads(t_rules *rules)
{
    int i = 0;
    while (i < rules->num_philo)
    {
        pthread_create(&rules->philos[i].thread, NULL, philo_routine,
            &rules->philos[i]);
        i++;
    }
}

static void join_threads(t_rules *rules)
{
    int i = 0;
    while (i < rules->num_philo)
    {
        pthread_join(rules->philos[i].thread, NULL);
        i++;
    }
}

int main(int argc, char **argv)
{
    t_rules rules;
    pthread_t monitor;

    if (init_rules(&rules, argc, argv))
    {
        printf("Error: invalid arguments\n");
        return (1);
    }
    rules.start_time = get_time();
    if (init_philosophers(&rules))
        return (1);
    create_threads(&rules);
    pthread_create(&monitor, NULL, monitor_routine, &rules);
    join_threads(&rules);
    pthread_join(monitor, NULL);
    destroy_mutexes(&rules);
    free(rules.forks);
    free(rules.philos);
    return (0);
}
