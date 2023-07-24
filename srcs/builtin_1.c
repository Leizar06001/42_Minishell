/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:41:56 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/24 19:37:42 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char **input)
{
	int	i;
	int	option;

	option = 0;
	i = 1;
	if (ft_strcmp(input[1], "-n") == 0)
	{
		option = 1;
		i++;
	}
	while (input[i])
	{
		add_str_to_output(input[i]);
		if (input[i + 1] != NULL)
			add_str_to_output(" ");
		i++;
	}
	if (option != 1)
		add_str_to_output("\n");
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
