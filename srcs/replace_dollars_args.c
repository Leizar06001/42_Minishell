/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollars_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:02:03 by mabdali           #+#    #+#             */
/*   Updated: 2023/08/08 18:02:36 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace_for_2quote(const char *arg, int *i, char deli)
{
	char	*tmp;

	arg = arg + 1;
	while (arg[*i] && arg[*i] != deli)
		(*i)++;
	if (arg[*i] && arg[*i] == deli)
	{
		while (arg[(*i) + 1])
			(*i)++;
	}
	tmp = malloc(sizeof(char) * (*i + 1));
	*i = 0;
	while (arg[*i] && arg[*i] != deli)
	{
		tmp[*i] = arg[*i];
		(*i)++;
	}
	if (arg[*i] && arg[*i] == deli)
	{
		while (arg[(*i) + 1])
		{
			tmp[*i] = arg[*i + 1];
			(*i)++;
		}
	}
	tmp[*i] = '\0';
	return (tmp);
}

int	find_var_name_end(char *var)
{
	int	i;

	i = 0;
	while ((var[i] >= 'A' && var[i] <= 'Z') || (var[i] >= 'a' && var[i] <= 'z')
		|| (var[i] >= '0' && var[i] <= '9'))
	{
		i++;
	}
	return (i);
}

char	*replace_just_dollar(int *start, char *tmp, char *arg)
{
	char	*value;
	char	*var_name;
	int		end;
	char	*tmp_var;

	var_name = ft_strdup(arg + *start + 1);
	end = find_var_name_end(var_name);
	if (var_name[ft_strlen(var_name) - 1] == '\'')
	{
		g_data.quote_before_dquotedollar = 1;
		var_name[ft_strlen(var_name) - 1] = '\0';
	}
	tmp_var = ft_strdup(var_name);
	tmp_var[end] = '\0';
	value = ft_getvar(tmp_var);
	free(tmp_var);
	if (g_data.quote_before_dquotedollar == 1)
		value = ft_strjoin(value, "\'");
	if (value)
		tmp_var = ft_strjoin(tmp, value);
	value = ft_strjoin(tmp_var, var_name + end);
	free(var_name);
	if (value)
	{
		free(tmp);
		free(tmp_var);
	}
	else
		return (tmp);
	return (value);
}

char	*replace_interogation(char *tmp)
{
	free(tmp);
	return (ft_itoa(g_data.exit_status));
}

char	*replace_dollar_var(char *arg, int i)
{
	char	*tmp;

	g_data.quote_before_dquotedollar = 0;
	if (!arg)
		return (NULL);
	if (arg[0] == '\'')
		return (replace_for_2quote(arg, &i, '\''));
	else if (arg[0] == '\"')
		return (replace_for_2quote(arg, &i, '\"'));
	if (ft_strchr(arg, '*'))
		return (ft_wildcards_main());
	i = 0;
	while (arg[i] && arg[i] != '$')
		i++;
	tmp = malloc(sizeof(char) * (i + 1));
	i = -1;
	while (arg[++i] && arg[i] != '$')
		tmp[i] = arg[i];
	tmp[i] = '\0';
	if (arg[i] == '$' && arg[i + 1] == '?')
		return (replace_interogation(tmp));
	else if (arg[i] == '$')
		return (replace_just_dollar(&i, tmp, arg));
	free(tmp);
	return (strdup(arg));
}

void	replace_dollar_args(char **cmd_line)
{
	char	*tmp;

	(void)cmd_line;
	g_data.actual_arg = 0;
	while (g_data.cur_cmd[g_data.actual_arg] != NULL)
	{
		tmp = replace_dollar_var(g_data.cur_cmd[g_data.actual_arg], 0);
		if (tmp)
		{
			free(g_data.cur_cmd[g_data.actual_arg]);
			g_data.cur_cmd[g_data.actual_arg] = tmp;
			g_data.actual_arg++;
		}
	}
}
