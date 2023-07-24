# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/21 17:07:37 by mabdali           #+#    #+#              #
#    Updated: 2023/07/20 17:41:36 by raphaellous      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                         DECLARATIONS DES VARIABLES                           #
################################################################################

NAME		=	minishell
NAME_TEST	=	test_main

CC			=	gcc

RM			=	rm -rf

FLAGS		:=	-g -Wall -Wextra -Werror

LREADLINE	:=	-lreadline

SRCS_PATH	:=	srcs

OBJS_PATH	:=	objs

SRCS_FILES	=	main.c 				\
				cmd_analyse_fnc.c	\
				ft_split.c			\
				ft_split_spaces.c	\
				ft_strjoin.c		\
				init.c				\
				init_struct.c		\
				utils_1.c			\
				utils_2.c			\
				utils_3.c			\
				free.c				\
				builtin_1.c			\
				ft_export.c			\
				ft_unset.c			\
				ft_chdir.c			\
				quote.c				\
				signals.c			\
				execve_main.c		\
				execve_fnc.c		\
				execve_utils.c		\
				parse.c				\
				redir_fnc.c			\
				redir_output.c		\
				output_functions.c	\
				replace_dollars_args.c	\
				cmd_launcher.c		\
				debug_utils.c

SRCS		=	$(addprefix $(SRCS_PATH)/, $(SRCS_FILES))

OBJS_FILES	=	$(SRCS_FILES:%.c=%.o)

OBJS		=	$(addprefix $(OBJS_PATH)/, $(OBJS_FILES))

SRCS_TEST_F	:=	$(subst main.c,main_test.c,$(SRCS_FILES))
SRCS_TEST	=	$(addprefix $(SRCS_PATH)/, $(SRCS_TEST_F))
OBJS_TEST_F	= 	$(SRCS_TEST_F:%.c=%.o)
OBJS_TEST	= 	$(addprefix $(OBJS_PATH)/, $(OBJS_TEST_F))

################################################################################
#                           INSTRUCTIONS DU MAKEFILE                           #
################################################################################

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c | $(OBJS_PATH)
	$(CC) $(FLAGS) -c $< -o $@

all		:	$(NAME)

test 	:	$(NAME_TEST)

$(NAME)	:	$(OBJS) | $(OBJS_PATH)
#	# @echo "\033[0;33m\nCOMPILING minishell ...\033[0m"
	$(CC) $(FLAGS) $(OBJS) $(LREADLINE) -o $(NAME)
#	# @echo "\033[1;32m./$(NAME) created\n\033[0m"

$(NAME_TEST)	:	$(OBJS_TEST) | $(OBJS_PATH)
#	@echo "\033[0;33m\nCOMPILING minishell ...\033[0m"
	$(CC) $(FLAGS) $(OBJS_TEST) $(LREADLINE) -o $(NAME_TEST)
#	@echo "\033[1;32m./$(NAME) created\n\033[0m"

$(OBJS_PATH):
	mkdir -p $(OBJS_PATH)

clean	:
	@clear
#	@echo "\033[0;31mDeleting $(NAME) object ...\033[0m"
	$(RM) $(OBJS)
#	@echo "\033[1;32mDone\033[0m\n"

fclean	:	clean
#	@echo "\033[0;31m\nDeleting $(NAME) executable ...\033[0m"
	$(RM) $(NAME)
#	@echo "\033[1;32mDone\033[0m\n"

cleantest	:
	@clear
#	@echo "\033[0;31mDeleting $(NAME_TEST) object ...\033[0m"
	$(RM) $(OBJS_TEST)
#	@echo "\033[1;32mDone\033[0m\n"

fcleantest	:	cleantest
#	@echo "\033[0;31m\nDeleting $(NAME_TEST) executable ...\033[0m"
	$(RM) $(NAME_TEST)
#	@echo "\033[1;32mDone\033[0m\n"

re: fclean all

rt: fcleantest test

.PHONY: all clean fclean re
