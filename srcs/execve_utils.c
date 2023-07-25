/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:07:59 by raphaellous       #+#    #+#             */
/*   Updated: 2023/07/25 13:55:32 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open_pipe(int *fd)
{
	int	status;

	status = pipe(fd);
	if (status == -1)
	{
		perror("msh: cannot create pipe\n");
		g_data.err = ERR_PIPE;
		clean_exit();
	}
	return (0);
}

int	ft_create_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("msh: cannot create fork\n");
		g_data.err = ERR_FORK;
		clean_exit();
	}
	return (pid);
}

int	ft_redir_pipe_read_to_stdin(int *fd)
{
	int	err;

	err = 0;
	close(fd[1]);
	err = dup2(fd[0], STDIN_FILENO);
	if (!err)
		g_data.stdin_to_default = 0;
	else
		perror("msh: error redirecting pipe to stdin\n");
	close(fd[0]);
	return (err);
}

int	ft_redir_pipe_write_to_stdout(int *fd)
{
	int	err;

	err = 0;
	close(fd[0]);
	if (g_data.fd_redir_out == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		if (!err)
			g_data.stdout_to_default = 0;
		else
			perror("msh: error redirecting pipe to stdout\n");
	}
	close(fd[1]);
	return (err);
}
