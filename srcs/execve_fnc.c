/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_fnc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:12:26 by raphaellous       #+#    #+#             */
/*   Updated: 2023/07/24 19:37:42 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
int	ft_call_execve(char **cmd, int ind, int create_pipe)
{
	pid_t	pid;
	int		fd[2];

	if (create_pipe)
		ft_open_pipe(fd);	// fd[1] write end / fd[0] read end
    pid = ft_create_fork();
	if (pid == 0)
	{
		if (create_pipe)	// redir output to pipe
			ft_redir_pipe_write_to_stdout(fd);
		if (execve(g_data.path_fnc[ind], cmd, NULL) == -1)
			printf("error exec\n");
		exit(1);
	}
	else
	{
		if (create_pipe)
			ft_redir_pipe_read_to_stdin(fd);
		waitpid(0, NULL, 0);
	}
	return (0);
}
*/
