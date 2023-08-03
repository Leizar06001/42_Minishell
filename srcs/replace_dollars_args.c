/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollars_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:02:03 by mabdali           #+#    #+#             */
/*   Updated: 2023/08/03 12:45:35 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace_for_2quote(const char *arg, int *i, char deli)
{
	char	*tmp;

	arg = arg + 1;
	while (arg[*i] && arg[*i] != deli)
		(*i)++;
	tmp = malloc(sizeof(char) * (*i + 1));
	*i = 0;
	while (arg[*i] && arg[*i] != deli)
	{
		tmp[*i] = arg[*i];
		(*i)++;
	}
	tmp[*i] = '\0';
	return (tmp);
}

char	*replace_just_dollar(int *i, char *tmp, char *arg)
{
	char	*value;
	char	*var_name;

	var_name = strdup(arg + *i + 1);
	if (var_name[ft_strlen(var_name) - 1] == '\'')
	{
		g_data.quote_before_dquotedollar = 1;
		var_name[ft_strlen(var_name) - 1] = '\0';
	}
	value = ft_getvar(var_name);
	if (g_data.quote_before_dquotedollar == 1)
		value = ft_strjoin(value, "\'");
	free(var_name);
	if (value == NULL)
		return (tmp);
	value = ft_strjoin(tmp, value);
	if (value)
		free(tmp);
	return (value);
}

char	*replace_interogation(char *tmp)
{
	free(tmp);
	return (ft_itoa(g_data.exit_status));
}

char	*replace_dollar_var(char *arg)
{
	int		i;
	char	*tmp;

	i = 0;
	g_data.quote_before_dquotedollar = 0;
	if (!arg)
	return(NULL);
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
		tmp = replace_dollar_var(g_data.cur_cmd[g_data.actual_arg]);
		if (tmp)
		{
			free(g_data.cur_cmd[g_data.actual_arg]);
			g_data.cur_cmd[g_data.actual_arg] = tmp;
			g_data.actual_arg++;
		}
	}
	g_data.cur_cmd[g_data.actual_arg] = NULL;
}
