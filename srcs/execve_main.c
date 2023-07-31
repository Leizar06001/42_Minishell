/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:36:08 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/31 14:34:34 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	cmd_return_value()
{
	if (WIFEXITED(g_data.cmd_ret))
		g_data.exit_status = WEXITSTATUS(g_data.cmd_ret);
	if (WIFSIGNALED(g_data.cmd_ret))
		g_data.exit_status = WTERMSIG(g_data.cmd_ret);
	if (WCOREDUMP(g_data.cmd_ret))
		g_data.exit_status = WCOREDUMP(g_data.cmd_ret);
	if (g_data.cmd_ret == 256)
		g_data.exit_status = 1;
}

int	find_fnc_path(void)
{
	int		i;
	char	*tmp;
	char	*fnc_slash;

	i = 0;
	fnc_slash = ft_strjoin("/", g_data.cur_args[0]);
	while (g_data.path_lst[i])
	{
		tmp = ft_strjoin(g_data.path_lst[i], fnc_slash);
		if (access(tmp, F_OK) == 0)
		{
			g_data.path_fnc = ft_strdup(tmp);
			free(tmp);
			free(fnc_slash);
			return (0);
		}
		i++;
		free(tmp);
	}
	free(fnc_slash);
	return (1);
}

int	exec_fnc_from_path(void)
{
	char	path[255];

	if (g_data.cur_args[0][0] == '.')
		g_data.path_fnc = ft_strjoin(getcwd(path, 255), g_data.cur_args[0] + 1);
	else if (g_data.cur_args[0][0] == '/')
		g_data.path_fnc = g_data.cur_args[0];
	if (access(g_data.path_fnc, F_OK) == 0)
		return (0);
	return (1);
}

int	ft_call_execve(int has_pipe)
{
	pid_t	pid;
	int		fd[2];

	if (has_pipe)
		ft_open_pipe(fd);
	pid = ft_create_fork();
	if (pid == -1)
		g_data.err = ERR_FORK;
	else if (pid == 0)
	{
		if (has_pipe)
			g_data.err = ft_redir_pipe_write_to_stdout(fd);
		if (execve(g_data.path_fnc, g_data.cur_args, g_data.env) != 0)
			printf("msh: error execve\n");
		clean_exit();
	}
	else
	{
		signal(SIGINT, handler_int_background);
		if (has_pipe)
			g_data.err = ft_redir_pipe_read_to_stdin(fd);
		waitpid(0, &g_data.cmd_ret, 0);
		signal(SIGINT, handler_int);
	}
	return (0);
}

int	ft_execve_launcher(int has_pipe)
{
	int		err;

	err = 0;
	if (g_data.cur_args[0][0] == '.' || g_data.cur_args[0][0] == '/')
		err = exec_fnc_from_path();
	else
		err = find_fnc_path();
	if (err)
		return (2);
	err = ft_call_execve(has_pipe);
	cmd_return_value();
	return (err);
}
