/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:15:31 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/28 19:05:13 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_env_rm_var(char **new_env, char *rm_var)
{
	int		i;
	int		j;
	char	**cur_var;
	int		removed;

	i = 0;
	j = 0;
	removed = 0;
	while (g_data.env[i])
	{
		cur_var = ft_split(g_data.env[i], '=');
		if (ft_strcmp(cur_var[0], rm_var) != 0)
		{
			new_env[j] = ft_strdup(g_data.env[i]);
			j++;
		}
		else
			removed++;
		free_2d(cur_var);
		i++;
	}
	g_data.nb_env_var -= removed;
}

void	ft_unset(char **cmd)
{
	int		i;
	char	**new_env;

	i = 0;
	while (cmd[++i])
	{
		if (check_var_name(cmd[i]))
		{
			new_env = (char **)malloc(sizeof(char *) * (g_data.nb_env_var + 1));
			if (new_env == NULL)
				return ;
			copy_env_rm_var(new_env, cmd[i]);
			new_env[g_data.nb_env_var] = NULL;
			free_2d(g_data.env);
			g_data.env = new_env;
		}
		else
			printf("minishell: unset: '%s': not a valid identifier\n", cmd[i]);
	}
	update_datas_from_env();
}
