# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/21 17:07:37 by mabdali           #+#    #+#              #
#    Updated: 2023/08/09 16:33:43 by rloussig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                         DECLARATIONS DES VARIABLES                           #
################################################################################

NAME		=	minishell

CC			=	gcc

RM			=	rm -rf

FLAGS		:=	-g -Wall -Wextra -Werror

LREADLINE	:=	-lreadline

SRCS_PATH	:=	srcs

OBJS_PATH	:=	objs

SRCS_FILES	=	main.c 				\
				cmd_analyse_fnc.c	\
				ft_split.c			\
				ft_parse.c			\
				ft_parse2.c			\
				ft_parse3.c			\
				ft_parse_utils.c	\
				ft_strjoin.c		\
				init.c				\
				init_struct.c		\
				utils_1.c			\
				utils_2.c			\
				utils_3.c			\
				utils_4.c			\
				free_fnc.c			\
				exit_fnc.c			\
				builtin_1.c			\
				ft_export.c			\
				ft_export_utils.c	\
				ft_unset.c			\
				ft_chdir.c			\
				quote_error.c		\
				pipe_error.c		\
				signals.c			\
				execve_main.c		\
				execve_utils.c		\
				redir_main.c		\
				redir_fnc.c			\
				redir_heredoc.c		\
				replace_dollars_args.c	\
				replace_dollars_utils.c	\
				cmd_launcher.c		\
				wildcards.c			\
				get_next_line.c		\
				debug_utils.c

SRCS		=	$(addprefix $(SRCS_PATH)/, $(SRCS_FILES))

OBJS_FILES	=	$(SRCS_FILES:%.c=%.o)

OBJS		=	$(addprefix $(OBJS_PATH)/, $(OBJS_FILES))

################################################################################
#                           INSTRUCTIONS DU MAKEFILE                           #
################################################################################

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c | $(OBJS_PATH)
	$(CC) $(FLAGS) -c $< -o $@

all		:	$(NAME)

$(NAME)	:	$(OBJS) | $(OBJS_PATH)
#	# @echo "\033[0;33m\nCOMPILING minishell ...\033[0m"
	$(CC) $(FLAGS) $(OBJS) $(LREADLINE) -o $(NAME)
#	# @echo "\033[1;32m./$(NAME) created\n\033[0m"

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

re: fclean all

.PHONY: all clean fclean re
