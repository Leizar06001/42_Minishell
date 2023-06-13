# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabdali <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/21 17:07:37 by mabdali           #+#    #+#              #
#    Updated: 2023/06/13 12:24:14 by mabdali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                         DECLARATIONS DES VARIABLES                           #
################################################################################

NAME		=	minishell

CC			=	gcc

RM			=	rm -rf

FLAGS		=	-g -Wall -Wextra -Werror

LREADLINE	=	-lreadline

SRCS_PATH	=	./srcs/

SRCS_FILES	=	main.c ft_split.c

SRCS		=	$(addprefix $(SRCS_PATH), $(SRCS_FILES))

OBJS		=	$(SRCS:.c=.o)

################################################################################
#                           INSTRUCTIONS DU MAKEFILE                           #
################################################################################

.c.o	:
	$(CC) $(FLAGS) -c $< -o $@

all		:	$(NAME)

$(NAME)	:	$(OBJS)
	@echo "\033[0;33m\nCOMPILING minishell ...\033[0m"
	$(CC) $(FLAGS) $(OBJS) $(LREADLINE) -o $(NAME)
	@echo "\033[1;32m./$(NAME) created\n\033[0m"

clean	:
	@echo "\033[0;31mDeleting $(NAME) object ...\033[0m"
	$(RM) $(OBJS)
	@echo "\033[1;32mDone\033[0m\n"

fclean	:	clean
	@echo "\033[0;31m\nDeleting $(NAME) executable ...\033[0m"
	$(RM) $(NAME)
	@echo "\033[1;32mDone\033[0m\n"

re: fclean all

.PHONY: all clean fclean re
