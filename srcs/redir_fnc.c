/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_fnc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:15:42 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/25 09:51:56 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	input_file(char *filename)
{
	int	err;

	err = 0;
	g_data.fd_redir_in = open(filename, O_RDONLY);
	if (g_data.fd_redir_in == -1)
	{
		printf("msh: no such file or directory: %s\n", filename);
		return (-1);
	}
	err = dup2(g_data.fd_redir_in, STDIN_FILENO);
	if (err == -1)
		printf("msh: error dup input fd\n");
	close(g_data.fd_redir_in);
	g_data.stdin_to_default = 0;
	return (err);
}

int	output_trunc(char *filename)
{
	int	err;

	err = 0;
	g_data.fd_redir_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (g_data.fd_redir_out == -1)
	{
		printf("msh: cannot create file: %s\n", filename);
		return (-1);
	}
	err = dup2(g_data.fd_redir_out, STDOUT_FILENO);
	if (err == -1)
		printf("msh: error dup output fd\n");
	close(g_data.fd_redir_out);
	g_data.stdout_to_default = 0;
	return (err);
}

int	output_append(char *filename)
{
	int	err;

	err = 0;
	g_data.fd_redir_out = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (g_data.fd_redir_out == -1)
	{
		printf("msh: cannot create file: %s\n", filename);
		return (-1);
	}
	err = dup2(g_data.fd_redir_out, STDOUT_FILENO);
	if (err == -1)
		printf("msh: error dup output fd\n");
	close(g_data.fd_redir_out);
	g_data.stdout_to_default = 0;
	return (err);
}

