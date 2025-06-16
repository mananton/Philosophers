#include "philo_bonus.h"

static void kill_all(t_rules *rules)
{
    int i = 0;

    while (i < rules->num_philo)
    {
        kill(rules->philos[i].pid, SIGTERM);
        i++;
    }
}

int wait_children(t_rules *rules)
{
    int status;
    pid_t pid;

    int i = 0;

    while (i < rules->num_philo)
    {
        pid = waitpid(-1, &status, 0);
        if (pid == -1)
            return (1);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
        {
            kill_all(rules);
            break;
        }
        i++;
    }
    return (0);
}
