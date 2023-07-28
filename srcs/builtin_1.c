/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:41:56 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/28 18:52:46 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char **input, int option)
{
	int	i;

	i = 0;
	if (input[1][0] == '-')
	{
		i = 1;
		while (input[1][i] == 'n')
			i++;
		if (input[1][i] == '\0')
		{
			option = 1;
			i = 1;
		}
		else
			i = 0;
	}
	while (input[++i])
	{
		printf("%s", input[i]);
		if (input[i + 1] != NULL)
			printf(" ");
	}
	if (option != 1)
		printf("\n");
}

char	*ft_getvar(char *varname)
{
	int		i;
	char	**cur_var;

	i = -1;
	while (g_data.env[++i])
	{
		cur_var = ft_split(g_data.env[i], '=');
		if (ft_strcmp(cur_var[0], varname) == 0)
		{
			free_2d(cur_var);
			return (ft_strchr(g_data.env[i], '=') + 1);
		}
		free_2d(cur_var);
	}
	return (NULL);
}

void	ft_env(void)
{
	int	i;

	i = -1;
	while (g_data.env[++i])
		printf("%s\n", g_data.env[i]);
}
