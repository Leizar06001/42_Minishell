/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_fnc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:07:54 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/25 09:21:39 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	close_fds(void)
{
	close(g_data.orig_fd_in);
	close(g_data.orig_fd_out);
}

static void	free_struct(void)
{
	// free(g_data.current_folder);
	free(g_data.minishell_name);
	// free(g_data.path_fnc);
	free_2d(g_data.path_lst);
	free_2d(g_data.env);
	free(g_data.user);
	// free_2d(g_data.cmd);
}

void	clean_exit(void)
{
	close_fds();
	free_struct();
	exit(0);
}
