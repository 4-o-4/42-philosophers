#include "./includes/philosophers.h"

static t_philo *setFork(int i, t_philo *philo, pthread_mutex_t *forkMutex) {
    philo[i].firstFork = forkMutex + i;
    philo[i].secondFork = forkMutex;
    while (i--) {
        philo[i].firstFork = forkMutex + i;
        philo[i].secondFork = forkMutex + i + 1;
    }
    return philo;
}

static t_philo *initPhilo(int argc, int *value, pthread_mutex_t *forkMutex) {
    t_philo *philo;
    int i;

    i = value[0];
    philo = (t_philo *)malloc(sizeof(t_philo) * i);
    if (!philo)
        return NULL;
    while (i--) {
        philo[i].id = i + 1;
        philo[i].value = value;
        philo[i].ut0 = ft_getTime();
        philo[i].arg5 = NULL;
        if (argc == ARG5)
            philo[i].arg5 = value + 4;
        pthread_mutex_init(forkMutex + i, NULL);
    }
    if (argc == ARG5)
        value[4] *= value[0];
    return setFork(value[0] - 1, philo, forkMutex);
}

static void createPhilo(int *value, t_philo *philo, pthread_t *threads) {
    int i;

    i = 0;
    while (i < value[0]) {
        pthread_create(threads + i, NULL, ft_philo, (void *) (philo + i));
        i += 2;
        if (i >= value[0] && !(i % 2))
            i = ft_oddCounter();
    }
}

static int startPhilo(int *value, pthread_mutex_t *forkMutex, t_philo *philo) {
    pthread_t *threads;
    int i;

    threads = (pthread_t *)malloc(sizeof(pthread_t) * (value[0] + 1));
    if (!threads)
        return 0;
    createPhilo(value, philo, threads);
    pthread_create(threads + value[0], NULL, ft_watcher, (void *) philo);
    i = 0;
    while (i < value[0])
        pthread_join(threads[i++], NULL);
    pthread_join(threads[value[0]], NULL);
    while (i--)
        pthread_mutex_destroy(forkMutex + i);
    free(threads);
    return 1;
}

int ft_init(int argc, int *value) {
    pthread_mutex_t *forkMutex;
    t_philo *philo;

    forkMutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * value[0]);
    if (!forkMutex)
        return ft_free(value, NULL, NULL);
    philo = initPhilo(argc, value, forkMutex);
    if (!philo)
        return ft_free(value, forkMutex, NULL);
    if (!startPhilo(value, forkMutex, philo))
        return ft_free(value, forkMutex, philo);
    return 1;
}
