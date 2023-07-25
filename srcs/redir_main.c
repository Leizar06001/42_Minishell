/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 09:41:10 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/25 12:12:00 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_do_redir(char *arrow, char *filename)
{
	int	err;

	err = 0;
	if (ft_strcmp(arrow, "<") == 0)
		err = input_file(filename);
	else if (ft_strcmp(arrow, ">") == 0)
		err = output_trunc(filename);
	else if (ft_strcmp(arrow, "<<") == 0)
		err = input_file(filename);
	else if (ft_strcmp(arrow, ">>") == 0)
		err = output_append(filename);
	return (err);
}

int	ft_reset_redirs(void)
{
	int	err;

	err = 0;
	if (!g_data.stdin_to_default)
		err = dup2(g_data.orig_fd_in, STDIN_FILENO);
	if (!err)
		g_data.stdin_to_default = 1;
	if (!g_data.stdout_to_default)
		err = dup2(g_data.orig_fd_out, STDOUT_FILENO);
	if (!err)
		g_data.stdin_to_default = 1;
	if (err == -1)
		printf("msh: error resetting redirections..\n");
	return (err);
}
