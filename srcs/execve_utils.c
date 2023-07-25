/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:07:59 by raphaellous       #+#    #+#             */
/*   Updated: 2023/07/25 10:00:11 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open_pipe(int *fd)
{
	int	status;

	status = pipe(fd);
	if (status == -1)
	{
		printf("PIPE ERROR\n");
		exit(1);
	}
	return (0);
}

int	ft_create_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("error fork\n");
		exit(1);
	}
	return (pid);
}

void	ft_redir_pipe_read_to_stdin(int *fd)
{
	int	err;

	err = 0;
	close(fd[1]);
	err = dup2(fd[0], STDIN_FILENO);
	if (!err)
		g_data.stdin_to_default = 0;
	close(fd[0]);
}

void	ft_redir_pipe_write_to_stdout(int *fd)
{
	int	err;

	err = 0;
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	if (!err)
		g_data.stdout_to_default = 0;
	close(fd[1]);
}
