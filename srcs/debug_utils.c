/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:34:53 by raphaellous       #+#    #+#             */
/*   Updated: 2023/07/28 18:53:33 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prt_array(char **arr)
{
	int	i;

	i = -1;
	printf(">> LIST : ");
	while (arr[++i])
	{
		printf("%s", arr[i]);
		if (arr[i + 1])
			printf(" / ");
	}
	printf("\n");
}

void	prt_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		printf("(arg[%d]:%s)\n", i, args[i]);
		i++;
	}
}
