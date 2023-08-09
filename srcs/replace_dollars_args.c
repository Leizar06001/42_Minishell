/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollars_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:02:03 by mabdali           #+#    #+#             */
/*   Updated: 2023/08/09 16:18:29 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replacefor2(const char *arg, int *i, char deli, char *tmp)
{
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
}

char	*replace_for_2quote(const char *arg, int *i, char deli)
{
	char	*tmp;
	char	*str;

	arg = arg + 1;
	if (deli == '\'' && (*arg == '>' || *arg == '<'))
	{
		str = ft_strdup(arg - 1);
		str[0] = 1;
		str[ft_strlen(str) - 1] = '\0';
		return (str);
	}
	while (arg[*i] && arg[*i] != deli)
		(*i)++;
	if (arg[*i] && arg[*i] == deli)
	{
		while (arg[(*i) + 1])
			(*i)++;
	}
	tmp = malloc(sizeof(char) * (*i + 1));
	*i = 0;
	replacefor2(arg, i, deli, tmp);
	return (tmp);
}

char	*replace_just_dollar(int *start, char *pre_str, char *arg)
{
	char	*value;
	char	*var_name;
	int		end;
	char	*tmp;

	var_name = ft_strdup(arg + *start + 1);
	end = ft_find_arg_name_end(var_name);
	var_name[end] = '\0';
	if (ft_isalnum(arg[*start + 1]))
		value = ft_strdup(ft_getvar(var_name));
	else
		value = ft_strdup("$");
	free(var_name);
	if (value == NULL)
	{
		value = ft_strjoin(pre_str, arg + *start + end + 1);
		free(pre_str);
		return (value);
	}
	tmp = ft_strjoin(pre_str, value);
	free(value);
	value = ft_strjoin(tmp, arg + *start + end + 1);
	free(tmp);
	free(pre_str);
	return (value);
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
		if (tmp && g_data.cur_cmd[g_data.actual_arg])
		{
			free(g_data.cur_cmd[g_data.actual_arg]);
			g_data.cur_cmd[g_data.actual_arg] = tmp;
			g_data.actual_arg++;
		}
	}
}
