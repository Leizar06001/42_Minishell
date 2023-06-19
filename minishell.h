/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:03:55 by mabdali           #+#    #+#             */
/*   Updated: 2023/06/19 11:31:39 by rloussig         ###   ########.fr       */
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
# include <sys/wait.h>

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
	char				*path_fnc;
	char				**env;
	int					nb_env_var;
	int					exit;
	int					testdquote;
	char				**path_lst;
	int					next_is_quote;
	int					prev_is_quote;
}				t_data;

extern t_data	data;

size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);

char	**ft_split(char const *s, char c);
char	**ft_split_spaces(char *str);

void	init_struct();
void	update_shell_name();

void	current_folder(void);
int 	ft_chdir(char *str);

char	*ft_strnstr(const char *str, const char *to_find, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);

char	*ft_strchr(const char *s, int c);
int 	ft_isalpha(int c);
int 	ft_isalnum(int c);
int 	ft_size_array(char **arr);
void	get_env_var(char **arr);

char    **ft_arraydup(char **arr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

void	free_2d(char **arr);
void	free_struct();
void	clean_exit();

void	ft_echo(char **input);
char    *ft_getvar(char *varname);
void    ft_env();

void    ft_export(char **cmd);
int 	check_var_name(char *str);

void    ft_unset(char **cmd);

void    handler_quit(int sig);
void	handler_int(int sig);

int		quote_error(char *str);

int		find_fnc_path(char *fnc_name);
int		ft_execve(char **cmd_line);


char **parse(char *cmd);

#endif