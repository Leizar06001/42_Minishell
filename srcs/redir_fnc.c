/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_fnc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:15:42 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/21 21:36:55 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_do_redir(char *arrow, char *filename)
{
	int	err;

	err = 0;
	if (ft_strcmp(arrow, "<") == 0)
	{
		data.orig_fd_in = dup(STDIN_FILENO);
		data.fd_redir_in = open(filename, O_RDONLY);
		printf("FDin: %d\n", data.fd_redir_in);
		err = dup2(data.fd_redir_in, STDIN_FILENO);
		if (err == -1)
			printf("msh: no such file or directory: %s\n", filename);
	}
	if (ft_strcmp(arrow, ">") == 0)
	{
		data.orig_fd_out = dup(STDOUT_FILENO);
		data.fd_redir_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		printf("FDout: %d\n", data.fd_redir_out);
        err = dup2(data.fd_redir_out, STDOUT_FILENO);
		if (err == -1)
			printf("msh: cannot create file: %s\n", filename);
	}
	return (err);
}

int	ft_reset_redirs()
{
	int	err;

	err = 0;
	if (data.fd_redir_in)
	{
		printf("Reset Redirs IN\n");
		err = dup2(data.orig_fd_in, STDIN_FILENO);
		close(data.fd_redir_in);
		data.fd_redir_in = 0;
	}
	if (data.fd_redir_out)
	{
		err = dup2(data.orig_fd_out, STDOUT_FILENO);
		close(data.fd_redir_out);
		printf("Reset Redirs OUT\n");
		data.fd_redir_out = 0;
	}
	if (err == -1)
		printf("ERROR RESET REDIRS\n");
	return (err);
}
