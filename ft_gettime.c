#include "./includes/philosophers.h"

long ft_gettime(void) {
    struct timeval current_time;

    gettimeofday(&current_time, NULL);
    return current_time.tv_sec * 1000 + current_time.tv_usec * 1e-3;
}
