/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 08:30:34 by raphaellous       #+#    #+#             */
/*   Updated: 2023/08/08 18:14:05 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char*	givequote(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = malloc(ft_strlen(str) + 3);
	tmp[i++] = '\'';
	while(str[j])
	{
		tmp[i++] = str[j++];
	}
	tmp[i++] = '\'';
	tmp[i] = '\0';
	return(tmp);
}

char	*dquote_parse(char **arr, char *str, int *i)
{
	char	*tmp;
	char	*tmp2;

	tmp = malloc_word_dquote(str, -1, 0);
	if (tmp[1] == '\'' && tmp[ft_strlen(tmp) - 2] == '\'')
	{
		tmp[ft_strlen(tmp) - 2] = '\0';
		tmp2 = replace_dollar_var(tmp + 2, 0);
		tmp2 = givequote(tmp2);
	}
	else
	{
		tmp[ft_strlen(tmp) - 1] = '\0';
		tmp2 = replace_dollar_var(tmp + 1, 0);
	}
	free(tmp);
	arr[*i] = ft_strdup(tmp2);
	free(tmp2);
	*i += 1;
	str = pass_word(str, '\"');
	joinquote(arr, i, '"');
	if (*str == '\"' || *str == '\'')
		g_data.next_is_quote = 1;
	if (*str && !ft_isspace(*str) && !ft_isthan(*str) && *str != '|')
		g_data.prev_is_dquote = 1;
	return (str);
}

char	*quote_parse(char **arr, char *str, int *i)
{
	char	*tmp;
	char	*tmp2;

	tmp = malloc_word_quote(str, -1, 0);
	tmp2 = replace_dollar_var(tmp, 0);
	free(tmp);
	arr[*i] = tmp2;
	*i += 1;
	str = pass_word(str, '\'');
	if (ft_strchr(tmp2, '$'))
		joinquote(arr, i, 'a');
	else
		joinquote(arr, i, '\'');
	if (*str == '\"' || *str == '\'')
		g_data.next_is_quote = 1;
	if (*str && !ft_isspace(*str) && !ft_isthan(*str) && *str != '|')
		g_data.prev_is_dquote = 1;
	return (str);
}

char	*morethan_parse(char **arr, char *str, int *i)
{
	if (*str == '>' && *(str + 1) == '>')
	{
		arr[*i] = ft_strdup(">>");
		str++;
	}
	else if (*str == '<' && *(str + 1) == '<')
	{
		arr[*i] = ft_strdup("<<");
		str++;
	}
	else
		arr[*i] = ft_strndup(str, 1);
	*i += 1;
	str++;
	return (str);
}

char	*pipe_parse(char **arr, char *str, int *i)
{
	if (*str == '|')
	{
		arr[*i] = ft_strdup("|");
		*i += 1;
		str++;
	}
	return (str);
}

char	*char_parse(char **arr, char *str, int *i)
{
	char	*tmp;
	char	*tmp2;

	arr[*i] = malloc_word(str);
	tmp2 = arr[*i];
	*i += 1;
	while (*str && !ft_isspace(*str) && !ft_is2quote(*str)
		&& !ft_isthan(*str) && *str != '|')
		str++;
	if (g_data.prev_is_dquote == 1 || g_data.prev_is_quote == 1)
	{
		if (g_data.prev_is_dquote == 1)
			arr[*i - 2] = remove_dquote(arr[*i - 2], '\"');
		else
			arr[*i - 2] = remove_dquote(arr[*i - 2], '\'');
		tmp = arr[*i - 2];
		arr[*i - 2] = ft_strjoin(arr[*i - 2], arr[*i - 1]);
		free(tmp);
		free(tmp2);
		*i -= 1;
		g_data.prev_is_dquote = 0;
		g_data.prev_is_quote = 0;
	}
	return (str);
}
