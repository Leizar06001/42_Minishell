/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:03:55 by mabdali           #+#    #+#             */
/*   Updated: 2023/08/01 17:53:57 by raphaellous      ###   ########.fr       */
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
# include <termios.h>

# define NC			"\e[0m"
# define YELLOW		"\e[33m"
# define BLUE		"\e[34m"
# define RED		"\e[91m"

# define WITHPIPE	1
# define NOPIPE		0

# define ERR_PIPE	11
# define ERR_FORK	10
# define ERR_EXEC	-15

# define CONTINUE	-99

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_data
{
	int				initialized;
	char			**main_env;
	char			*user;
	char			*path;
	char			*home;
	char			*cwd;
	char			*minishell_name;
	char			*line;
	char			*cmd;
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
	int				next_is_dquote;
	int				prev_is_dquote;
	int				quote_before_dquotedollar;
	char			*output;
	int				i_splitspaces;
	int				orig_fd_in;
	int				orig_fd_out;
	int				stdin_to_default;
	int				stdout_to_default;
	int				fd_redir_in;
	int				fd_redir_out;
	int				err;
	char			*heredoc;
	int				cmd_ret;
	int				exit_status;
	char			*strsplit;
	char			**wildcard_res;
}				t_data;

extern t_data	g_data;

size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);

char	**ft_split(char const *s, char c);

char	**ft_split_spaces(char *str, int i);
char	*pipe_split(char **arr, char *str, int i);
char	*morethan(char **arr, char *str, int i);
char	*just_character(char **arr, char *str, int i);
void	joinquote(char **arr, int *i, char c);
char	*pass_word(char *str, char c);
int		ft_isspace(char c);
int		ft_isthan(char c);
char	*remove_dquote(char *str, char c);
char	*ft_strndup(char *str, int n);
char	*malloc_word(char *str);

char	**ft_parse(char *str, int i);

void	init_struct(char **env);
void	update_datas_from_env(void);

void	init_shlvl(void);
void	update_shell_name(void);

void	current_folder(void);
int		ft_chdir(char *str);

int		init_cmd_line_analyser(void);
int		cmd_line_analyser(int err, int size_cmd, int i);

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
char	*ft_itoa(int n);
int		ft_atoi(const char *str);

int		ft_check_arrows(char *str);
int		str_only_space_tab(char *str);

void	free_2d(char **arr);

void	clean_exit(void);

void	ft_echo(char **input, int option);
char	*ft_getvar(char *varname);
void	ft_env(void);
void	export_no_arg(void);

int		ft_export(char **cmd);
int		check_var_name(char *str);

void	copy_env(char **new_env);
int		check_var_name(char *str);

void	ft_unset(char **cmd);

void	handler_int(int sig);
void	handler_int_background(int sig);

//quote_error.c
int		quote_error(char *str);

//pipe_error.c
int		is_last_char_pipe(char *str);
int		two_pipes_with_space(char *str);

// NEW FUNCTIONS EXEC + PIPE + REDIR

int		ft_redir_pipe_write_to_stdout(int *fd);
int		ft_redir_pipe_read_to_stdin(int *fd);
int		ft_create_fork(void);
int		ft_open_pipe(int *fd);

int		find_fnc_path(void);
int		exec_fnc_from_path(void);
int		ft_call_execve(int has_pipe);
int		ft_execve_launcher(int has_pipe);

int		ft_cmd_laucher_main(int has_pipe);
int		ft_reset_redirs(void);

int		ft_do_redir(char *arrow, char *filename);
int		ft_reset_redirs(void);
int		ft_reset_files_redir(void);
// ---------------------------------

int		ft_wildcards_main(char *cmd);

char	**replace_dollar_args(char **cmd_line);
char	*replace_dollar_var(const char *arg);

int		output_append(char *filename);
int		output_trunc(char *filename);
int		input_file(char *filename);
int		input_heredoc(char *delimiter, int err);

// Get next line
char	*ft_remain(char *buf);
char	*ft_return_line(char *buf);
char	*ft_read_buf(int fd, char *ret);
char	*get_next_line(int fd);
void	*ft_calloc(size_t nb, size_t size);

//	****** DEBUG FUNCTIONS ******
void	prt_args(char **args);
void	prt_array(char **arr);

#endif
