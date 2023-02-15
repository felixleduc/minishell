# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 10:50:59 by fleduc            #+#    #+#              #
#    Updated: 2023/02/14 21:28:24 by fleduc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Werror -Wall -Wextra -g
RM = rm -rf

LIBFT = @$(MAKE) -sC ./libft
LIBFTA = ./libft/libft.a

HEADERS = include/minishell.h
SRCS = src/minishell.c src/parse.c src/separate_args.c src/variables.c src/utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS) $(OBJS) $(HEADERS)
	$(LIBFT)
	#$(CC) $(CFLAGS) -lreadline -L $(HOME)/.brew/opt/readline/lib -I $(HOME)/.brew/opt/readline/include $(LIBFTA) $(OBJS) -o $(NAME)
	#$(CC) $(CFLAGS) -lreadline -L /opt/homebrew/Cellar/readline/8.2.1/lib -I /opt/homebrew/Cellar/readline/8.2.1/include $(LIBFTA) $(OBJS) -o $(NAME)
	$(CC) $(CFLAGS) -lreadline -L ./readline/8.2.1/lib -I ./readline/8.2.1/include $(LIBFTA) $(OBJS) -o $(NAME)

clean:
	$(LIBFT) clean
	$(RM) $(OBJS)

fclean:	clean
	$(LIBFT) fclean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re noshell

.SILENT: all $(NAME) clean fclean $(OBJS) noshell