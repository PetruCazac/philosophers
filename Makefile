# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/08 18:38:30 by pcazac            #+#    #+#              #
#    Updated: 2023/10/18 11:33:24 by pcazac           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

VPATH = src obj src/print;

SRC = philo.c philo_work.c init_check.c struct_utils.c utils.c philo_utils.c

OBJ = $(SRC:%.c=$(OBJ_PATH)/%.o)
OBJ_PATH = obj

CC= cc
CFLAGS= -g -pthread -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJ_PATH)/%.o : %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
