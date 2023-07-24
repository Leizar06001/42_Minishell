/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:07:54 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/24 19:37:42 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_struct(void)
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
	free_struct();
	exit(0);
}
