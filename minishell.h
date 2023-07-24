/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:03:55 by mabdali           #+#    #+#             */
/*   Updated: 2023/07/24 19:38:17 by raphaellous      ###   ########.fr       */
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
# include <string.h>

# define NC			"\e[0m"
# define YELLOW		"\e[33m"
# define BLUE		"\e[34m"
# define WITHPIPE	1
# define NOPIPE		0

typedef struct s_data
{
	char			*user;
	char			*path;
	char			*home;
	char			*cwd;
	char			*minishell_name;
	char			*line;
	char			**cmd;
	char			**cur_cmd;
	char			**cur_args;
	char			*current_folder;
	char			*path_fnc;
	char			**env;
	int				nb_env_var;
	int				exit;
	int				testdquote;
	char			**path_lst;
	int				next_is_quote;
	int				prev_is_quote;
	int             prev_is_dquote;
	int				quote_before_dquotedollar;
	char			*output;
	int				i_splitspaces;
	int				orig_fd_in;
	int				orig_fd_out;
	int				fd_redir_in;
	int				fd_redir_out;
}				t_data;

extern t_data	g_data;

size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);

char	**ft_split(char const *s, char c);
char	**ft_split_spaces(char *str);

void	init_struct(char **env);
void	update_shell_name(void);

void	current_folder(void);
int		ft_chdir(char *str);

int		cmd_line_analyser(int id_cmd);

char	*ft_strnstr(const char *str, const char *to_find, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);

char	*ft_strchr(const char *s, int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_size_array(char **arr);
void	get_env_var(char **arr);

char	**ft_arraydup_plus_one(char **arr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

void	free_2d(char **arr);
void	free_struct(void);
void	clean_exit(void);

void	ft_echo(char **input);
char	*ft_getvar(char *varname);
void	ft_env(void);

void	ft_export(char **cmd);
int		check_var_name(char *str);

void	ft_unset(char **cmd);

void	handler_quit(int sig);
void	handler_int(int sig);

int		quote_error(char *str);


// NEW FUNCTIONS EXEC + PIPE + REDIR

void	ft_redir_pipe_write_to_stdout(int *fd);
void	ft_redir_pipe_read_to_stdin(int *fd);
int		ft_create_fork();
int		ft_open_pipe(int *fd);


int		find_fnc_path();
int		exec_fnc_from_path();
int		ft_execve();
int		ft_call_execve(int has_pipe);
int		ft_execve_launcher(int has_pipe);

int		ft_builtin_fnc(char **cmd);
int 	ft_cmd_laucher_main(int has_pipe);
int		ft_reset_redirs();

int		ft_do_redir(char *arrow, char *filename);
int		ft_reset_redirs();
// ---------------------------------


void	select_output(char **cmd_line);
void	add_str_to_output(char *str);

void	ft_redir_output(char **cmd_line);

char	**parse(char *cmd);

char	**replace_dollar_args(char **cmd_line);

//	****** DEBUG FUNCTIONS ******
void	prt_args(char **args);
void    prt_array(char **arr);

#endif
