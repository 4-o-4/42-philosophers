#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <ctype.h> // isdigit

# define ERROR "\e[31mError:\e[0m"
# define INT_LEN 10

int     *ft_parser(const int argc, char **argv);
int     ft_error(char *str);

long    ft_gettime(void);

#endif
