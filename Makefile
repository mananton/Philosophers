NAME=philo
NAME_BONUS=philo_bonus

all:
	$(MAKE) -C philo

bonus:
	$(MAKE) -C philo_bonus

clean:
	$(MAKE) clean -C philo
	$(MAKE) clean -C philo_bonus

fclean:
	$(MAKE) fclean -C philo
	$(MAKE) fclean -C philo_bonus

re: fclean all

.PHONY: all bonus clean fclean re
