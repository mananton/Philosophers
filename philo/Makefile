NAME=philo
CC=cc
CFLAGS=-Wall -Wextra -Werror -pthread
SRC=main.c philosophers.c philo_actions.c monitor.c utils.c rules.c parse.c
OBJ=$(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
