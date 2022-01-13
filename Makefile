NAME = philo

INCLUDE = -I includes/

SRC = ft_gettime.c \
      ft_init.c \
      ft_parser.c \
      ft_philo.c \
      main.c

LIBS = -lpthread

CC = gcc $(FLAGS)

FLAGS = -Wall -Wextra -Werror

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean:
	make clean
	rm -f $(NAME)

re: fclean all
