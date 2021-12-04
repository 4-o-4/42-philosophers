#include "./includes/philosophers.h"

static void swapMutex(pthread_mutex_t **firstFork, pthread_mutex_t **secondFork) {
    pthread_mutex_t *c = *firstFork;
    *firstFork = *secondFork;
    *secondFork = c;
}

static t_philo *setFork(int i, t_philo *philo, pthread_mutex_t *forkMutex) {
    while (i--) {
        philo[i].firstFork = forkMutex + i;
        if (!i)
            philo[i].secondFork = forkMutex + philo->value[0] - 1;
        else
            philo[i].secondFork = forkMutex + i - 1;
        if (i % 2 != 0)
            swapMutex(&(philo + i)->firstFork, &(philo + i)->secondFork);
    }
    return philo;
}

static t_philo *initPhilo(int *value, pthread_mutex_t *forkMutex) {
    t_philo *philo;
    int i;

    i = value[0];
    philo = (t_philo *)malloc(sizeof(t_philo) * i);
    if (!philo)
        return NULL;
    while (i--) {
        philo[i].id = i;
        philo[i].value = value;
        pthread_mutex_init(forkMutex + i, NULL);
    }
    return setFork(value[0], philo, forkMutex);
}

int ft_init(int argc, int *value) {
    pthread_mutex_t *forkMutex;
    t_philo *philo;

    forkMutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * value[0]);
    if (!forkMutex)
        return 0;
    philo = initPhilo(value, forkMutex);
    if (!philo)
        return 0;

    return 1;
}
