/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_fnc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:07:54 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/31 18:11:08 by raphaellous      ###   ########.fr       */
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
	free(g_data.minishell_name);
	free_2d(g_data.path_lst);
	free_2d(g_data.env);
	free(g_data.user);
}

void	clean_exit(void)
{
	printf(" --- Clean Exit ---\n");
	close_fds();
	free_struct();
	exit(g_data.err);
}
