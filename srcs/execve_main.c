/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:36:08 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/25 16:40:50 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (execve(g_data.path_fnc, g_data.cur_args, g_data.env) == -1)
			printf("msh: error execve\n");
		exit(127);
		clean_exit();
	}
	else
	{
		if (has_pipe)
			g_data.err = ft_redir_pipe_read_to_stdin(fd);
		waitpid(0, NULL, 0);
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
		return (-1);
	err = ft_call_execve(has_pipe);
	return (err);
}
