# Makefile
NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = philo.c philo_utils.c philo_monitor.c philo_print.c philo_init.c philo_simulation.c philo_action.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
