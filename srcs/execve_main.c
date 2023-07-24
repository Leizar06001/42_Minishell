/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:36:08 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/24 18:11:58 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_fnc_path()
{
	//printf("> Find path: %s\n", data.cur_args[0]);
	int		i;
	char	*tmp;
	char	*fnc_slash;

	i = 0;
	fnc_slash = ft_strjoin("/", data.cur_args[0]);
	while (data.path_lst[i])
	{
		tmp = ft_strjoin(data.path_lst[i], fnc_slash);
		if (access(tmp, F_OK) == 0)
		{
			data.path_fnc = ft_strdup(tmp);
			//printf("> Path for %s: %s\n", data.cur_args[0], data.path_fnc);
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

int	exec_fnc_from_path()
{
	//printf("> Exec from path: %s\n", data.cur_args[0]);
	char	path[255];

	if (data.cur_args[0][0] == '.')
		data.path_fnc = ft_strjoin(getcwd(path, 255), data.cur_args[0] + 1);
	else if (data.cur_args[0][0] == '/')
		data.path_fnc = data.cur_args[0];
	if (access(data.path_fnc, F_OK) == 0)
		return (0);
	return (1);
}



int	ft_execve()
{
	pid_t	pid;
	int		err;

	if (data.cur_args[0][0] == '.' || data.cur_args[0][0] == '/')
		err = exec_fnc_from_path();
	else
		err = find_fnc_path();
	if (err)
		return (1);
	
	pid = fork();
	if (pid == 0)
	{
		if (execve(data.path_fnc, data.cur_args, data.env) == -1)
			printf("error exec\n");
		exit(1);
	}
	else
	{
		waitpid(0, NULL, 0);
		free_2d(data.cur_args);
	}
	return (0);
}


int	ft_call_execve(int has_pipe)
{
	pid_t	pid;
	int		fd[2];

	if (has_pipe)
		ft_open_pipe(fd);	// fd[1] write end / fd[0] read end
    pid = ft_create_fork();
	if (pid == 0)
	{
		if (has_pipe)	// redir output to pipe
			ft_redir_pipe_write_to_stdout(fd);
		//printf("Start cmd\n");
		//printf("RESULT:\n");
		if (execve(data.path_fnc, data.cur_args, NULL) == -1)
			printf("error exec\n");
		exit(1);
	}
	else
	{
		if (has_pipe)
		{
			ft_redir_pipe_read_to_stdin(fd);
		}
		waitpid(0, NULL, 0);
	}
	return (0);
}

int	ft_execve_launcher(int has_pipe)
{
	int		err;

	err = 0;
	if (data.cur_args[0][0] == '.' || data.cur_args[0][0] == '/')
		err = exec_fnc_from_path();
	else
		err = find_fnc_path();
	if (err)
		return (1);
	err = ft_call_execve(has_pipe);
	return (err);
}
