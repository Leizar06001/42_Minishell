/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:08:09 by rloussig          #+#    #+#             */
/*   Updated: 2023/08/01 14:56:26 by mabdali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*malloc_word_dquote(char *str, int i, int len)
{
	char	*word;

	if (str[len] == '\"')
		len++;
	while (str[len] && str[len] != '\"')
		len++;
	if (str[len] == '\"')
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (++i < len)
	{
		if (*(str - 1) == '"')
			g_data.prev_is_dquote = 1;
		else if (*(str - 1) == '\'')
			g_data.prev_is_quote = 1;
		else
			g_data.prev_is_quote = 0;
		word[i] = str[i];
	}
	if (str[i - 1] == '\"' || str[i - 1] == '\'')
		g_data.prev_is_quote = 1;
	word[i] = '\0';
	return (word);
}

char	*malloc_word_quote(char *str, int i, int len)
{
	char	*word;

	if (str[len] == '\'')
		len++;
	while (str[len] && str[len] != '\'')
		len++;
	if (str[len] == '\'')
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (++i < len)
	{
		if (*(str - 1) == '\"')
			g_data.prev_is_dquote = 1;
		else if (*(str - 1) == '\'')
			g_data.prev_is_quote = 1;
		else
			g_data.prev_is_quote = 0;
		word[i] = str[i];
	}
	if (str[i - 1] == '\"' || str[i - 1] == '\'')
		g_data.prev_is_quote = 1;
	word[i] = '\0';
	return (word);
}

char	*dquote_ss(char **arr, char *str, int i)
{
	arr[i++] = malloc_word_dquote(str, -1, 1);
	str = pass_word(str, '\"');
	joinquote(arr, i, '"');
	g_data.i_splitspaces = i;
	return (str);
}

char	*quote_ss(char **arr, char *str, int i)
{
	arr[i++] = malloc_word_quote(str, -1, 1);
	str = pass_word(str, '\'');
	joinquote(arr, i, '\'');
	g_data.i_splitspaces = i;
	return (str);
}

char	**ft_split_spaces(char *str, int i)
{
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * (1000));
	if (!arr)
		return (NULL);
	g_data.strsplit = str;
	while (*str)
	{
		while (*str && ft_isspace(*str))
			str++;
		if (*str && *str == '"')
			str = dquote_ss(arr, str, i);
		else if (*str && *str == '\'')
			str = quote_ss(arr, str, i);
		else if (*str && !ft_isspace(*str) && *str != '>'
			&& *str != '<' && *str != '|')
			str = just_character(arr, str, i);
		else if (*str && (*str == '>' || *str == '<'))
			str = morethan(arr, str, i);
		else if (*str && *str == '|')
			str = pipe_split(arr, str, i);
		i = g_data.i_splitspaces;
	}
	arr[i] = NULL;
	return (arr);
}
