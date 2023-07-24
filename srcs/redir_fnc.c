/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_fnc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:15:42 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/24 20:03:08 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_do_redir(char *arrow, char *filename)
{
	int	err;

	err = 0;
	if (ft_strcmp(arrow, "<") == 0)
	{
		// g_data.orig_fd_in = dup(STDIN_FILENO);
		// printf("BACKUP STDIN %d\n", g_data.orig_fd_in);
		g_data.fd_redir_in = open(filename, O_RDONLY);
		//printf("STDIN to '%s' fd: %d\n", filename, g_data.fd_redir_in);
		err = dup2(g_data.fd_redir_in, STDIN_FILENO);
		if (err == -1)
			printf("msh: no such file or directory: %s\n", filename);
	}
	if (ft_strcmp(arrow, ">") == 0)
	{
		g_data.orig_fd_out = dup(STDOUT_FILENO);
		//printf("BACKUP STDOUT %d\n", g_data.orig_fd_out);
		g_data.fd_redir_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		//printf("STDOUT to '%s' fd: %d\n", filename, g_data.fd_redir_out);
        err = dup2(g_data.fd_redir_out, STDOUT_FILENO);
		if (err == -1)
			printf("msh: cannot create file: %s\n", filename);
	}
	return (err);
}

int	ft_reset_redirs(void)
{
	int	err;

	err = 0;
	//printf("Reset Redirs IN to %d\n", g_data.orig_fd_in);
	err = dup2(g_data.orig_fd_in, STDIN_FILENO);
	if (g_data.fd_redir_in)
	{
		//printf("Closing FDin %d\n", g_data.fd_redir_in);
		close(g_data.fd_redir_in);
		g_data.fd_redir_in = 0;
	}
	err = dup2(g_data.orig_fd_out, STDOUT_FILENO);
	if (g_data.fd_redir_out)
	{
		//printf("Closing FDout %d\n", g_data.fd_redir_out);
		close(g_data.fd_redir_out);
		//printf("Reset Redirs OUT to %d\n", g_data.orig_fd_out);
		g_data.fd_redir_out = 0;
	}
	if (err == -1)
		printf("ERROR RESET REDIRS\n");
	return (err);
}
