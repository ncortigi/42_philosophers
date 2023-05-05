# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncortigi <ncortigi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 14:07:58 by ncortigi          #+#    #+#              #
#    Updated: 2023/05/05 14:55:34 by ncortigi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRC		= check_input.c death.c ft_close.c living.c \
			main.c set.c utils.c print.c

OBJ		= $(SRC:.c=.o)

CC		= gcc
RM		= rm -f
CFLAGS  = -g -Wall -Wextra -Werror -pthread

$(NAME):                $(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJ)

fclean:		clean
				$(RM) $(OBJ) $(NAME)

re:		fclean all