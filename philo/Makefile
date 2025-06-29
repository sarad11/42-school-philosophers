# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saradominguez <saradominguez@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/17 10:30:55 by saradomingu       #+#    #+#              #
#    Updated: 2025/05/17 11:03:57 by saradomingu      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

FLAGS = -Wall -Werror -Wextra -g

SCR = main.c params_checkers.c init_philo_process.c init.c init_mutexes.c init_mutexes2.c thread.c join.c action.c checkers.c is_death.c utils.c print.c error.c destroy.c destroy2.c free.c

OBJ = $(SCR:.c=.o)

INCLUDE = philo.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(FLAGS)

%.o: %.c $(INCLUDE)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
