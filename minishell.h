/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:03:55 by mabdali           #+#    #+#             */
/*   Updated: 2023/08/02 14:53:27 by raphaellous      ###   ########.fr       */
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
	int				actual_arg;
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

//ft strjoin
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_and_free(char *s1, char *s2);
// ft split
char	**ft_split(char const *s, char c);
// parse
char	**ft_parse(char *str, int i);
char	*remove_dquote(char *str, char c);
void	joinquote(char **arr, int *i, char c);
// parse 2
char	*malloc_word_dquote(char *str, int i, int len);
char	*malloc_word_quote(char *str, int i, int len);
char	*malloc_word(char *str);
char	*pass_word(char *str, char c);
//	parse 3
char	*char_parse(char **arr, char *str, int *i);
char	*pipe_parse(char **arr, char *str, int *i);
char	*morethan_parse(char **arr, char *str, int *i);
char	*quote_parse(char **arr, char *str, int *i);
char	*dquote_parse(char **arr, char *str, int *i);
// parse utils
char	*ft_strndup(char *str, int n);
int		ft_is2quote(char c);
int		ft_isthan(char c);
int		ft_isspace(char c);
// init struct
void	init_struct(char **env);
void	update_datas_from_env(void);
// init
void	init_shlvl(void);
void	update_shell_name(void);
// ft chdir
void	current_folder(void);
int		ft_chdir(char *str);
// cmd analyse fnc
int		init_cmd_line_analyser(void);
int		cmd_line_analyser(int err, int size_cmd, int i);
// utils 1
char	*ft_strnstr(const char *str, const char *to_find, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
// utils 2
char	*ft_strchr(const char *s, int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_size_array(char **arr);
void	get_env_var(char **arr);
// utils 3
char	**ft_arraydup_plus_one(char **arr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
// utils 4
int		ft_check_arrows(char *str);
int		str_only_space_tab(char *str);
// free fnc
void	free_2d(char **arr);
// exit fnc
void	clean_exit(void);
// builtin 1
void	ft_echo(char **input, int option);
char	*ft_getvar(char *varname);
void	ft_env(void);
void	export_no_arg(void);
// ft export
int		ft_export(char **cmd);
int		check_var_name(char *str);
// ft export utils
void	copy_env(char **new_env);
int		check_var_name(char *str);
// ft unset
void	ft_unset(char **cmd);
// signals
void	handler_int(int sig);
void	handler_int_background(int sig);
//quote_error.c
int		quote_error(char *str);
//pipe_error.c
int		is_last_char_pipe(char *str);
int		two_pipes_with_space(char *str);
// NEW FUNCTIONS EXEC + PIPE + REDIR
// execve utils
int		ft_redir_pipe_write_to_stdout(int *fd);
int		ft_redir_pipe_read_to_stdin(int *fd);
int		ft_create_fork(void);
int		ft_open_pipe(int *fd);
// execve main
int		find_fnc_path(void);
int		exec_fnc_from_path(void);
int		ft_call_execve(int has_pipe);
int		ft_execve_launcher(int has_pipe);
// cmd launcher
int		ft_cmd_laucher_main(int has_pipe);
int		ft_reset_redirs(void);
// redir main
int		ft_do_redir(char *arrow, char *filename);
int		ft_reset_redirs(void);
int		ft_reset_files_redir(void);
// redir fnc
int		output_append(char *filename);
int		output_trunc(char *filename);
int		input_file(char *filename);
int		input_heredoc(char *delimiter, int err);
// wildcards
char	*ft_wildcards_main(void);
// replace dollars args
void	replace_dollar_args(char **cmd_line);
char	*replace_dollar_var(char *arg);
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
