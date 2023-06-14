/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:03:55 by mabdali           #+#    #+#             */
/*   Updated: 2023/06/14 14:31:47 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>

# define NC		"\e[0m"
# define YELLOW	"\e[33m"
# define BLUE	"\e[34m"

typedef struct	s_data
{
	char				*user;
	char				*path;
	char				*home;
	char				*minishell_name;
	char				*line;
	char				**cmd;
	char				*current_folder;
	char				*echo_path;
	char				*path_fnc;
	char				**env;
	int					exit;
	struct sigaction	sa;
}				t_data;

extern t_data	data;

size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);

char	*ft_strjoin(char const *s1, char const *s2);

char	**ft_split(char const *s, char c);
char	**ft_split_spaces(char *str);

void	init_struct();
void	find_sys_functions();
void	update_shell_name();

void    init_signals(void);

void	current_folder(void);
int 	ft_chdir(char *str);

char	*ft_strnstr(const char *str, const char *to_find, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strrchr(const char *s, int c);

void	free_struct();

void	ft_echo(char **input);
void    ft_env();
void    ft_export(char **cmd);
void    ft_unset(char **cmd);

void	get_env_var(char **arr);

void	handler(int sig, siginfo_t *info, void *ucontext);

int quote_error(char *str);
#endif