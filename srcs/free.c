/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:07:54 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/20 18:07:02 by raphaellous      ###   ########.fr       */
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
	// free(data.current_folder);
	free(data.minishell_name);
	// free(data.path_fnc);
	free_2d(data.path_lst);
	free_2d(data.env);
	free(data.user);
	// free_2d(data.cmd);
}

void	clean_exit(void)
{
	free_struct();
	exit(0);
}
