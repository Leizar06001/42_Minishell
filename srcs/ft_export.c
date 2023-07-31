/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:09:14 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/31 13:18:27 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_var_name(char *str)
{
	int	i;

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

static void	copy_env(char **new_env)
{
	int	i;

	i = -1;
	while (++i < g_data.nb_env_var)
		new_env[i] = ft_strdup(g_data.env[i]);
	new_env[i] = NULL;
}

static int	check_var_exists(char *var, char *new_line)
{
	int		i;
	char	**cur_var;

	i = -1;
	while (g_data.env[++i])
	{
		cur_var = ft_split(g_data.env[i], '=');
		if (ft_strcmp(cur_var[0], var) == 0)
		{
			free(g_data.env[i]);
			g_data.env[i] = ft_strdup(new_line);
			free_2d(cur_var);
			return (1);
		}
		free_2d(cur_var);
	}
	return (0);
}

static void	ft_sub_export(char **cmd, int i)
{
	char	**new_env;

	new_env = malloc(sizeof(char *) * (g_data.nb_env_var + 2));
	if (new_env == NULL)
		return ;
	copy_env(new_env);
	new_env[g_data.nb_env_var] = ft_strdup(cmd[i]);
	new_env[g_data.nb_env_var + 1] = NULL;
	free_2d(g_data.env);
	g_data.env = new_env;
	g_data.nb_env_var++;
}

void	ft_export(char **cmd)
{
	int		i;
	char	**new_var;

	i = 0;
	while (cmd[++i])
	{
		if (ft_strchr(cmd[i], '=') && ft_strlen(cmd[i]) > 1 && cmd[i][0] != '=')
		{
			new_var = ft_split(cmd[i], '=');
			if (check_var_name(new_var[0]))
			{
				if (!check_var_exists(new_var[0], cmd[i]))
					ft_sub_export(cmd, i);
			}
			else
				printf("minishell: export: '%s': not a valid identifier\n",
					new_var[0]);
			free_2d(new_var);
		}
	}
	if (!cmd[1])
		export_no_arg();
	update_datas_from_env();
}
