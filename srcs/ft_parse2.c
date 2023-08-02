/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 08:26:54 by raphaellous       #+#    #+#             */
/*   Updated: 2023/08/02 08:35:06 by raphaellous      ###   ########.fr       */
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
		word[i] = str[i];
	}
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
		word[i] = str[i];
	}
	word[i] = '\0';
	return (word);
}

char	*malloc_word(char *str)
{
	char	*word;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (str[len] && !ft_isspace(str[len]) && !ft_is2quote(str[len])
		&& !ft_isthan(str[len]) && str[len] != '|')
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	while (str[i] && !ft_isspace(str[i]) && !ft_is2quote(str[i])
		&& !ft_isthan(str[i]) && str[i] != '|')
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	if (str[i] == '\"')
		g_data.next_is_dquote = 1;
	if (str[i] == '\'')
		g_data.next_is_quote = 1;
	return (word);
}

char	*pass_word(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			str++;
		while (*str != c && *str)
			str++;
		if (*str == c)
		{
			str++;
			break ;
		}
	}
	return (str);
}
