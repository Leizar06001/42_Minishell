/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:40:22 by raphaellous       #+#    #+#             */
/*   Updated: 2023/08/01 12:52:11 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_var_name(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = -1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
	}
	return (1);
}

void	copy_env(char **new_env)
{
	int	i;

	i = -1;
	while (++i < g_data.nb_env_var)
		new_env[i] = ft_strdup(g_data.env[i]);
	new_env[i] = NULL;
}
