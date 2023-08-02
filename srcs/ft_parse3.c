/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 08:30:34 by raphaellous       #+#    #+#             */
/*   Updated: 2023/08/02 11:27:05 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*dquote_parse(char **arr, char *str, int *i)
{
	arr[*i] = malloc_word_dquote(str, -1, 0);
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
	arr[*i] = malloc_word_quote(str, -1, 0);
	*i += 1;
	str = pass_word(str, '\'');
	joinquote(arr, i, 'a');
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
	arr[*i] = malloc_word(str);
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
		arr[*i - 2] = ft_strjoin(arr[*i - 2], arr[*i - 1]);
		arr[*i - 1] = NULL;
		*i -= 1;
		g_data.prev_is_dquote = 0;
		g_data.prev_is_quote = 0;
	}
	return (str);
}
