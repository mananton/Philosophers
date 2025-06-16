NAME=philo_bonus
CC=cc
CFLAGS=-Wall -Wextra -Werror -pthread
SRC=main.c philosophers_bonus.c monitor_bonus.c utils_bonus.c \
 rules_bonus.c parse_bonus.c
OBJ=$(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c philo_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
