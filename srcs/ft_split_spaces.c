/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:08:09 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/31 18:03:36 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*malloc_word(char *str)
{
	char	*word;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (str[len] && !ft_isspace(str[len]) && str[len] != '\"'
		&& str[len] != '>' && str[len] != '<' && str[len] != '|')
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	while (str[i] && !ft_isspace(str[i]) && str[i] != '\"' && str[i] != '>'
		&& str[i] != '<' && str[i] != '|')
	{
		word[i] = str[i];
		i++;
	}
	if (str[i] == '\"')
		g_data.next_is_quote = 1;
	word[i] = '\0';
	return (word);
}

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

char	**ft_split_spaces(char *str)
{
	char	**arr;
	int		i;

	i = 0;
	arr = (char **)malloc(sizeof(char *) * (1000));
	if (!arr)
		return (NULL);
	while (*str)
	{
		while (*str && ft_isspace(*str))
			str++;
		if (*str && *str == '"')
		{
			arr[i++] = malloc_word_dquote(str, -1, 1);
			str = pass_word(str, '\"');
			joinquote(arr, i, '"');
		}
		else if (*str && *str == '\'')
		{
			arr[i++] = malloc_word_quote(str, -1, 1);
			str = pass_word(str, '\'');
			joinquote(arr, i, '\'');
		}
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
