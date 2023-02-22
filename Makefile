# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 10:50:59 by fleduc            #+#    #+#              #
#    Updated: 2023/02/22 12:45:00 by fleduc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Werror -Wall -Wextra -g
RM = rm -rf

LIBFT = @$(MAKE) -sC ./libft
LIBFTA = ./libft/libft.a

SRCS = src/minishell.c src/parse.c src/separate_args.c \
	   src/variables.c src/utils.c src/pipes.c src/redirections.c \
	   src/builtins.c src/builtins2.c src/export.c src/utils2.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(LIBFT)
	$(CC) $(CFLAGS) -lreadline -L ./readline/8.2.1/lib -I ./readline/8.2.1/include $(LIBFTA) $(OBJS) -o $(NAME)

clean:
	$(LIBFT) clean
	$(RM) $(OBJS)

fclean:	clean
	$(LIBFT) fclean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re

.SILENT: all $(NAME) clean fclean $(OBJS)
