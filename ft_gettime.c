#include "philosophers.h"
#include <unistd.h>
#include <sys/time.h>

long ft_getTime(void) {
    struct timeval current_time;

    gettimeofday(&current_time, NULL);
    return current_time.tv_sec * 1000 + current_time.tv_usec * 1e-3;
}

void ft_usleep(long time, t_philo *philo) {
    long i;

    i = ft_getTime() + time;
    while (i > ft_getTime() && philo->value[1])
        usleep(100);
}

int ft_oddCounter(void) {
    usleep(10);
    return 1;
}

int ft_free(int *value, pthread_mutex_t *forkMutex, t_philo *philo) {
    free(value);
    if (forkMutex)
        free(forkMutex);
    if (philo)
        free(philo);
    return 0;
}
