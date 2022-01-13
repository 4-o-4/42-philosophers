#include "philosophers.h"

static void takeFork(t_philo *philo, int forks) {
    if (forks) {
        pthread_mutex_lock(philo->firstFork);
        pthread_mutex_lock(philo->secondFork);
    } else {
        pthread_mutex_unlock(philo->firstFork);
        pthread_mutex_unlock(philo->secondFork);
    }
}

static void printStatus(t_philo *philo, int status) {
    long time;

    time = ft_getTime();
    if (status == eating && philo->value[1]) {
        printf("%li\t%d has taken a fork\n", time - philo->ut0, philo->id);
        printf("%li\t%d is eating\n", time - philo->ut0, philo->id);
        if (philo->arg5)
            (*philo->arg5)--;
        ft_usleep(philo->value[2], philo);
    } else if (status == sleeping && philo->value[1]) {
        printf("%li\t%d is sleeping\n", time - philo->ut0, philo->id);
        ft_usleep(philo->value[3], philo);
        if (philo->value[1])
            printf("%li\t%d is thinking\n", time - philo->ut0, philo->id);
    }
}

static int isDied(t_philo *philo) {
    long time;

    time = ft_getTime();
    if (time - philo->ut0 - philo->ut1 > philo->value[1]) {
        philo->value[1] = 0;
        printf("\e[31m%li\t%d is dead\e[0m\n", time - philo->ut0, philo->id);
        return 0;
    } else if (philo->arg5 && !*philo->arg5) {
        philo->value[1] = 0;
        return 0;
    }
    return 1;
}

void *ft_watcher(void *tid) {
    t_philo *philo;
    int i;

    philo = (t_philo *)tid;
    i = 0;
    while (!(i ^= i))
        while (i < philo->value[0])
            if (!isDied(philo + i++))
                pthread_exit(NULL);
    pthread_exit(NULL);
}

void *ft_philo(void *tid) {
    t_philo *philo;

    philo = (t_philo *)tid;
    philo->ut1 = 0;
    while (philo->value[1] && philo->value[0] != 1) {
        takeFork(philo, lock);
        philo->ut1 = ft_getTime() - philo->ut0;
        printStatus(philo, eating);
        takeFork(philo, unlock);
        printStatus(philo, sleeping);
    }
    pthread_exit(NULL);
}
