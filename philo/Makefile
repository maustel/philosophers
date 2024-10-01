# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/05 14:29:49 by maustel           #+#    #+#              #
#    Updated: 2024/10/01 10:10:44 by maustel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo
FLAGS = -Wall -Wextra -Werror
# FLAGS = -Wall -Wextra

SRCS = main.c free.c parsing.c init.c safe_functions.c meal.c utils.c get_set.c output.c supervision.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	cc $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	cc $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
