#include "./includes/philosophers.h"
#include <unistd.h> // usleep

typedef struct  s_philo {
    int         id;
    const int   *value;
}               t_philo;

pthread_mutex_t *forkMutex;
int *heldBy;
int *prevUsedBy;

void *philosopher(void *tid) {
    t_philo *philo;
    long t;
    int thisID;
    int count;
    int firstFork;
    int secondFork;

    philo = (t_philo *)tid;
    thisID = philo->id;
    count = philo->value[0];
    if (thisID != count - 1) {
        firstFork = thisID;
        secondFork = thisID + 1;
    } else {
        firstFork = 0;
        secondFork = count - 1;
    }

    t = ft_gettime();
    for (int i = 0; i < 3; i++) {
        pthread_mutex_lock(&forkMutex[firstFork]);
        heldBy[firstFork] = thisID;
        while (prevUsedBy[secondFork] == thisID) {
            if (prevUsedBy[firstFork] == thisID) {
                pthread_mutex_unlock(&forkMutex[firstFork]);
                heldBy[firstFork] = -1;
                prevUsedBy[firstFork] = -1;
            }
        }
        pthread_mutex_lock(&forkMutex[secondFork]);
        heldBy[secondFork] = thisID;
        if (heldBy[firstFork] != thisID) {
            pthread_mutex_lock(&forkMutex[firstFork]);
            heldBy[firstFork] = thisID;
        }
        usleep(philo->value[2] * 1000);

        heldBy[firstFork] = -1;
        prevUsedBy[firstFork] = thisID;
        pthread_mutex_unlock(&forkMutex[secondFork]);
        heldBy[secondFork] = -1;
        prevUsedBy[secondFork] = thisID;
        pthread_mutex_unlock(&forkMutex[firstFork]);

        usleep(philo->value[3] * 1000);
        printf("%d | Время: %ld\n", thisID + 1, ft_gettime() - t);
    }
    pthread_exit(NULL);
}


int main(int argc, char **argv) {
    int *value = NULL;

    if (argc < 5 || argc > 6)
        printf("Error: ...\n");
    else if (!(value = ft_parser(argc, argv)))
        return (1);

    t_philo *philo;
    pthread_t threads[value[0] + 1];
    int i;

    philo = (t_philo *)malloc(sizeof(t_philo) * value[0]);
    forkMutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * value[0]);
    heldBy = (int *)malloc(sizeof(int) * value[0]);
    prevUsedBy = (int *)malloc(sizeof(int) * value[0]);

    for (i = 0; i < value[0]; i++) {
        philo[i].id = i;
        philo[i].value = value;
        pthread_mutex_init(&forkMutex[i], NULL);
        heldBy[i] = -1;
        prevUsedBy[i] = i;
    }
    for (i = 0; i < value[0]; i++) {
        pthread_create(&threads[i], NULL, philosopher, (void *)(philo + i));
    }
    for (i = 0; i < value[0]; i++)
        pthread_join(threads[i], NULL);
    for (i = 0; i < value[0]; i++)
        pthread_mutex_destroy(&forkMutex[i]);

    free(philo);
    free(forkMutex);
    free(heldBy);
    free(value);

    return (0);
}
