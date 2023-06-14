/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:07:54 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/14 19:14:59 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_2d(char **arr)
{
	int i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	if (arr)
		free(arr);
}

void	free_struct()
{
	// free(data.current_folder);
	// free(data.minishell_name);
	// free(data.path_fnc);
	// free_2d(data.path_lst);
	// free_2d(data.env);
	// free_2d(data.cmd);
}

void	clean_exit()
{
	free_struct();
	exit(0);
}
