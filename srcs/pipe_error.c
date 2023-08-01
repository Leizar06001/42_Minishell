/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:01:01 by rloussig          #+#    #+#             */
/*   Updated: 2023/08/01 12:08:13 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_last_char_pipe(char *str)
{
	int	len;
	int	i;

	len = strlen(str);
	i = len - 1;
	if (len == 0)
		return (0);
	while (i >= 0 && str[i] == ' ')
		i--;
	if (i >= 0 && str[i] == '|')
	{
		printf("msh: error: expected expression after pipe\n");
		return (-1);
	}
	return (0);
}

int	two_pipes_with_space(char *str)
{
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = 0;
	while (str[i] && !(pipe_count == 2))
	{
		if (str[i] == '|')
		{
			pipe_count++;
			if (pipe_count == 2)
			{
				printf("msh: error: two consecutive pipes\n");
				return (-1);
			}
		}
		else if (str[i] > ' ')
			pipe_count = 0;
		i++;
	}
	return (0);
}
